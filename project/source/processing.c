/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:37:22 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/16 11:02:33 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_fill_fmat(t_imat *data_in, t_fmat *init_mat, float *center, float im_diag);

void	create_init_mat(t_imat *data_in, t_fmat *init_mat, t_image *im)
{
	int		n_pts;
	float	center[2]; // to replace by float point struct
	float	im_diag; //image diagonal for scaling

	im_diag = sqrt(pow(im -> nx - 1, 2) + pow(im -> ny - 1, 2));
	center[0] = 0.5 * (data_in -> n - 1);
	center[1] = 0.5 * (data_in -> m - 1);
	n_pts = data_in -> m * data_in -> n;
	init_mat -> m = 3;
	init_mat -> n = n_pts;
	init_mat -> fmat = (float *)malloc(sizeof(float) * n_pts * 3);
	if (init_mat -> fmat == NULL)
	{
		free(data_in -> imat);
		perror("In create_init_mat");
		exit(EXIT_FAILURE);
	}
	_fill_fmat(data_in, init_mat, center, im_diag);
	return ; //need to free data in here?
}

static void	_fill_fmat(t_imat *data_in, t_fmat *init_mat, float *center, float im_diag)
//normalisation so that model fits exactly within image (accounting x y only)
{
	int	cc;
	int	i;
	int	j;
	float	scale_fact;
 	int	nb_pts;

	nb_pts = data_in -> m * data_in -> n;
	//norm = 0.01;// sqrt(x_cent * x_cent + y_cent * y_cent); //remove 1 later (used for debug)
	scale_fact = 0.5 * im_diag / sqrt(center[0] * center[0] + center[1] * center[1]);
	cc = 0;
	i = 0;
	while (i < data_in -> m)
	{
		j = 0;
		while (j < data_in -> n)
		{
			(init_mat -> fmat)[cc] = (i - center[0]) * scale_fact;
			(init_mat -> fmat)[cc + nb_pts] = (j - center[1]) * scale_fact;
			(init_mat -> fmat)[cc + 2 * nb_pts] =
				(data_in -> imat)[i * data_in -> n + j] * scale_fact;
			j++;
			cc++;
		}
		i++;
	}
	return ;
}
