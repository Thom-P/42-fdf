/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:37:22 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/18 19:04:48 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_fill_fmat(t_imat *data_in, t_fmat *init_mat, float *center, float im_diag);

void	_assign_transfo_mat(float *rotz_mat, float *rotx_mat, t_view *view);

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

//print_fmat(rotz);
//print_fmat(rotx);
//rotation and zoom/z-stretch
void	transform_fmat(t_fmat *fmat, t_view *view)
{
	t_fmat	rotz;
	t_fmat	rotx;
	float	rotz_mat[9];
	float	rotx_mat[9];

	rotz.m = 3;
	rotz.n = 3;
	rotx.m = 3;
	rotx.n = 3;
	_assign_transfo_mat(rotz_mat, rotx_mat, view);
	rotz.fmat = rotz_mat;
	rotx.fmat = rotx_mat;
	premult_fmat(&rotx, &rotz);
	premult_fmat(&rotz, fmat);
	//premult_fmat(&rotz, fmat);
	//premult_fmat(&rotx, fmat);
	return ;
}

void	_assign_transfo_mat(float *rotz_mat, float *rotx_mat, t_view *view)
{
	rotz_mat[0] = view -> zoom * cosf(view -> theta_z);
	rotz_mat[1] = view -> zoom * -sinf(view -> theta_z);
	rotz_mat[2] = 0.;
	rotz_mat[3] = view -> zoom * sinf(view -> theta_z);
	rotz_mat[4] = view -> zoom * cosf(view -> theta_z);
	rotz_mat[5] = 0.;
	rotz_mat[6] = 0.;
	rotz_mat[7] = 0.;
	rotz_mat[8] = view -> zoom * 1.;
	rotx_mat[0] = 1.;
	rotx_mat[1] = 0.;
	rotx_mat[2] = 0.;
	rotx_mat[3] = 0.;
	rotx_mat[4] = cosf(view -> theta_x);
	rotx_mat[5] = -sinf(view -> theta_x);
	rotx_mat[6] = 0.;
	rotx_mat[7] = sinf(view -> theta_x);
	rotx_mat[8] = cosf(view -> theta_x);
	return ;
}

