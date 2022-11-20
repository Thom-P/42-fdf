/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:37:22 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/20 15:00:42 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_fill_fmat(t_imat *data_in, t_fmat *init_mat, float *center, float im_diag);

//void	_assign_transfo_mat(float *rotz_mat, float *rotx_mat, t_view *view);
void	_assign_transfo_mat(float *transfo_mat, t_view *view);

void	create_init_fmat(t_imat *data_in, t_fmat *init_fmat, t_image *im)
{
	int		n_pts;
	float	center[2]; // to replace by float point struct
	float	im_radius; //image size for scaling (chose ny, usually smaller)

	im_radius = 0.5 * (im -> ny - 1);
	center[0] = 0.5 * (data_in -> n - 1);
	center[1] = 0.5 * (data_in -> m - 1);
	n_pts = data_in -> m * data_in -> n;
	init_fmat -> m = 3;
	init_fmat -> n = n_pts;
	init_fmat -> fmat = (float *)malloc(sizeof(float) * n_pts * 3);
	if (init_fmat -> fmat == NULL)
	{
		free(data_in -> imat);
		perror("In create_init_mat");
		exit(EXIT_FAILURE);
	}
	_fill_fmat(data_in, init_fmat, center, im_radius);
	return ; //need to free data in here?
}

static void	_fill_fmat(t_imat *data_in, t_fmat *init_fmat, float *center, float im_radius)
//normalisation so that model fits exactly within image (accounting x y only)
//0.95 prefact to allow some margin
//flip the z sign so that elevation goes from screen to user (z axis backward)
{
	int	cc;
	int	i;
	int	j;
	float	scale_fact;
 	int	nb_pts;

	nb_pts = data_in -> m * data_in -> n;
	scale_fact = 0.95 * im_radius / sqrt(center[0] * center[0] + center[1] * center[1]);
	cc = 0;
	i = 0;
	while (i < data_in -> m)
	{
		j = 0;
		while (j < data_in -> n)
		{
			(init_fmat -> fmat)[cc] = (j - center[0]) * scale_fact; //x
			(init_fmat -> fmat)[cc + nb_pts] = (i - center[1]) * scale_fact; //y
			(init_fmat -> fmat)[cc + 2 * nb_pts] =
				-1. * (data_in -> imat)[i * data_in -> n + j] * scale_fact; //z
			j++;
			cc++;
		}
		i++;
	}
	return ;
}

//rotation and zoom/z-stretch
void	transform_fmat(t_fmat *fmat, t_view *view)
{
	t_fmat	transfo;
	float	transfo_mat[9];

	transfo.m = 3;
	transfo.n = 3;
	_assign_transfo_mat(transfo_mat, view);
	transfo.fmat = transfo_mat;
	premult_fmat(&transfo, fmat);
	return ;
}

void	_assign_transfo_mat(float *transfo_mat, t_view *view)
{
	float 	cz;
	float	sz;
	float	cx;
	float	sx;
	float 	zoom;

	cz = cosf(view -> theta_z); 
	sz = sinf(view -> theta_z); 
	cx = cosf(view -> theta_x); 
	sx = sinf(view -> theta_x); 
	zoom = view -> zoom;
	transfo_mat[0] = zoom * cz;
	transfo_mat[1] = zoom * -sz;
	transfo_mat[2] = 0.;
	transfo_mat[3] = zoom * cx * sz;
	transfo_mat[4] = zoom * cx * cz;
	transfo_mat[5] = view -> z_scale * zoom * -sx;
	transfo_mat[6] = zoom * sx * sz;
	transfo_mat[7] = zoom * sx * cz;
	transfo_mat[8] = view -> z_scale * zoom * cx;
	return ;
}

//get projected and shifted matrix
int	*proj_shift(t_fmat *fmat, t_image *im, t_view *view, int **is_in_im)
{
	int	*proj_mat;
	int nb_pts;
	int	i;

	nb_pts = fmat -> n;
	proj_mat = (int *)malloc(2 * nb_pts *sizeof(int));
	*is_in_im = (int *)malloc(nb_pts * sizeof(int));
	if (proj_mat == NULL || *is_in_im == NULL)
	{
		free(proj_mat); //need clean fct
		free(is_in_im);
		free(fmat -> fmat); //shd also close window and all... create clean fct!
		perror("In proj_mat");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < nb_pts)
	{
		(*is_in_im)[i] = 1;
		proj_mat[i] = round((fmat -> fmat)[i] + 0.5 * im -> nx + view -> off_x); // also recenter and shift
		if (proj_mat[i] < 0 || proj_mat[i] > im -> nx - 1)
			(*is_in_im)[i] = 0;
		proj_mat[i + nb_pts] =  round((fmat -> fmat)[i + nb_pts] + 0.5 * im -> ny + view -> off_y);
		if (proj_mat[i + nb_pts] < 0 || proj_mat[i + nb_pts] > im -> ny - 1)
			(*is_in_im)[i] = 0;
		//proj_mat[i + 2 * nb_pts] =  round((fmat -> fmat)[i + 2 * nb_pts]); //to replace later for z-scale color
		i++;
	}
	return (proj_mat);
}
