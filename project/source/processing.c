/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:37:22 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/17 12:36:51 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_fill_fmat(t_imat *data_in, t_fmat *init_mat, float *center, float im_diag);

void	_assign_rotmats(float *rotz_mat, float *rotx_mat, float theta_z, float theta_x);

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
	//norm = 0.01;// sqrt(x_cent * x_cent + y_cent * y_cent); //remove 1 later (used for debug)
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

void	rotate_fmat(t_fmat *fmat, float theta_z, float theta_x)
{
	t_fmat	rotZ;
	t_fmat	rotX;
	float	rotz_mat[9];
	float	rotx_mat[9];

	rotZ.m = 3;
	rotZ.n = 3;
	rotX.m = 3;
	rotX.n = 3;
	_assign_rotmats(rotz_mat, rotx_mat, theta_z, theta_x);
	rotZ.fmat = rotz_mat;
	rotX.fmat = rotx_mat;
	//print_fmat(rotZ);
	//print_fmat(rotX);
	premult_fmat(&rotZ, fmat);
	premult_fmat(&rotX, fmat);
	return ;
}

void	_assign_rotmats(float *rotz_mat, float *rotx_mat, float theta_z, float theta_x)
{
	rotz_mat[0] = cosf(theta_z);
	rotz_mat[1] = -sinf(theta_z);
	rotz_mat[2] = 0.;
	rotz_mat[3] = sinf(theta_z);
	rotz_mat[4] = cosf(theta_z);
	rotz_mat[5] = 0.;
	rotz_mat[6] = 0.;
	rotz_mat[7] = 0.;
	rotz_mat[8] = 1.;
	rotx_mat[0] = 1.;
	rotx_mat[1] = 0.;
	rotx_mat[2] = 0.;
	rotx_mat[3] = 0.;
	rotx_mat[4] = cosf(theta_x);
	rotx_mat[5] = -sinf(theta_x);
	rotx_mat[6] = 0.;
	rotx_mat[7] = sinf(theta_x);
	rotx_mat[8] = cosf(theta_x);
	return ;
}

