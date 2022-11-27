/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:37:22 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/27 18:49:07 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_fill_fmat(t_imat *data_in, t_fmat *fmat, float *ctr, float im_rad);

static void	_assign_transfo_mat(float *transfo_mat, t_view *view);

// Convert initial int data into 3D float matrix (x, y, z)
void	create_init_fmat(t_imat *data_in, t_fmat *init_fmat, t_image *im, t_view *view)
{
	int		n_pts;
	float	center[2];
	float	im_size;

	im_size = 0.5 * (im -> ny - 1);
	center[0] = 0.5 * (data_in -> n - 1);
	center[1] = 0.5 * (data_in -> m - 1);
	n_pts = data_in -> m * data_in -> n;
	init_fmat -> m = 3;
	init_fmat -> n = n_pts;
	init_fmat -> fmat = (float *)malloc(sizeof(float) * n_pts * 3);
	if (init_fmat -> fmat == NULL)
	{
		free(data_in -> imat);
		free(view -> i_color);
		perror("In create_init_mat");
		exit(EXIT_FAILURE);
	}
	_fill_fmat(data_in, init_fmat, center, im_size);
	return ;
}

/* Norm. distances so that model fits within image (diagonal should fit in ny)
(0.95 prefactor to allow some margin)
Flip the z sign so that elev. goes from screen to user (z axis pointing back)*/
static void	_fill_fmat(t_imat *data_in, t_fmat *fmat, float *ctr, float im_size)
{
	int		cc;
	int		i;
	int		j;
	float	scale_fact;
	int		nb_pts;

	nb_pts = data_in -> m * data_in -> n;
	scale_fact = 0.95 * im_size / sqrt(pow(ctr[0], 2) + pow(ctr[1], 2));
	cc = 0;
	i = 0;
	while (i < data_in -> m)
	{
		j = 0;
		while (j < data_in -> n)
		{
			(fmat -> fmat)[cc] = (j - ctr[0]) * scale_fact;
			(fmat -> fmat)[cc + nb_pts] = (i - ctr[1]) * scale_fact;
			(fmat -> fmat)[cc + 2 * nb_pts]
				= -1. * (data_in -> imat)[i * data_in -> n + j] * scale_fact;
			j++;
			cc++;
		}
		i++;
	}
	return ;
}

// Apply rotation and zoom/z-stretch
void	transform_fmat(t_fmat *curr_fmat, t_fmat *init_fmat, t_view *view)
{
	t_fmat	transfo;
	float	transfo_mat[9];

	transfo.m = 3;
	transfo.n = 3;
	_assign_transfo_mat(transfo_mat, view);
	transfo.fmat = transfo_mat;
	mult_fmat(curr_fmat, &transfo, init_fmat);
	return ;
}

// Implement rotation and zoom/z-stretch matrix
static void	_assign_transfo_mat(float *transfo_mat, t_view *view)
{
	float	cz;
	float	sz;
	float	cx;
	float	sx;
	float	zoom;

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

// Get (x, y) projected, recentered, and shifted (from WASD) matrix
int	*proj_shift(t_fmat *fmat, t_meta *meta, int **is_in_im)
{
	int		*proj;
	int		i;
	t_image	*im;
	t_view	*view;

	im = &meta -> im;
	view = &meta -> view;
	proj = (int *)malloc(2 * fmat -> n * sizeof(int));
	*is_in_im = (int *)malloc(fmat -> n * sizeof(int));
	if (proj == NULL || *is_in_im == NULL)
		free_and_exit(fmat -> fmat, meta ->init_fmat.fmat, meta -> view.i_color);
	i = 0;
	while (i < fmat -> n)
	{
		(*is_in_im)[i] = 1;
		proj[i] = round((fmat -> fmat)[i] + 0.5 * im -> nx + view -> off_x);
		if (proj[i] < 0 || proj[i] > im -> nx - 1)
			(*is_in_im)[i] = 0;
		proj[i + fmat -> n] = round((fmat -> fmat)[i + fmat -> n]
				+ 0.5 * im -> ny + view -> off_y);
		if (proj[i + fmat -> n] < 0 || proj[i + fmat -> n] > im -> ny - 1)
			(*is_in_im)[i] = 0;
		i++;
	}
	return (proj);
}
