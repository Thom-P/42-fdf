/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:37:22 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/15 14:33:10 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_fill_fmat(t_imat *data_in, t_fmat *init_mat, float x_cent, float y_cent);

void	create_init_mat(t_imat *data_in, t_fmat *init_mat)
{
	int		n_pts;
	float	x_cent;
	float	y_cent;

	x_cent = 0.5 * (data_in -> n - 1);
	y_cent = 0.5 * (data_in -> m - 1);
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
	_fill_fmat(data_in, init_mat, x_cent, y_cent);
	return ;
}

static void	_fill_fmat(t_imat *data_in, t_fmat *init_mat, float x_cent, float y_cent)
//normalisation so that model within dist 1 from origin (on x y only)
{
	int	cc;
	int	i;
	int	j;
	float	norm;
 	int	nb_pts;

	nb_pts = data_in -> m * data_in -> n;
	norm = sqrt(x_cent * x_cent + y_cent * y_cent);
	cc = 0;
	i = 0;
	while (i < data_in -> m)
	{
		j = 0;
		while (j < data_in -> n)
		{
			(init_mat -> fmat)[cc] = (i - x_cent) / norm;
			(init_mat -> fmat)[cc + nb_pts] = (j - y_cent) / norm;
			(init_mat -> fmat)[cc + 2 * nb_pts] =
				(data_in -> imat)[i * data_in -> n + j] / norm;
			j++;
			cc++;
		}
		i++;
	}
	return ;
}




