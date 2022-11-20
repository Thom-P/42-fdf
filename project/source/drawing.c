/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:18:28 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/20 15:24:37 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_draw_edge_r(int *proj_mat, int cc, t_imat *data_in, t_image *im);

static void	_draw_edge_d(int *proj_mat, int cc, t_imat *data_in, t_image *im);

void	draw_grid_image(int *proj_mat, int *in_im, t_image *im, t_imat *data_in)
{
	int	i;
	int	j;
	int	cc;

	cc = 0;
	while (cc < data_in -> m * data_in -> n)
	{
		if (!in_im[cc])
		{	
			cc++;
			continue ;
		}
		i = cc / data_in -> n;
		j = cc % data_in -> n;
		if (j < data_in -> n - 1 && in_im[cc + 1])
			_draw_edge_r(proj_mat, cc, data_in, im);
		if (i < data_in -> m - 1 && in_im[cc + data_in -> n])
			_draw_edge_d(proj_mat, cc, data_in, im);
		cc++;
	}
	return ;
}

static void	_draw_edge_r(int *proj_mat, int cc, t_imat *data_in, t_image *im)
{	
	int		nb_pts;
	t_ipt2	p;
	t_ipt2	p_right;

	nb_pts = data_in -> m * data_in -> n;
	p.x = proj_mat[cc];
	p.y = proj_mat[cc + nb_pts];
	p_right.x = proj_mat[cc + 1];
	p_right.y = proj_mat[cc + 1 + nb_pts];
	draw_line_image(&p, &p_right, im);
	return ;
}

static void	_draw_edge_d(int *proj_mat, int cc, t_imat *data_in, t_image *im)
{	
	int		nb_pts;
	t_ipt2	p;
	t_ipt2	p_down;

	nb_pts = data_in -> m * data_in -> n;
	p.x = proj_mat[cc];
	p.y = proj_mat[cc + nb_pts];
	p_down.x = proj_mat[cc + data_in -> n];
	p_down.y = proj_mat[cc + data_in -> n + nb_pts];
	draw_line_image(&p, &p_down, im);
	return ;
}

void	draw_box_around_image(t_image *im)
{	
	t_ipt2	top_left;
	t_ipt2	top_right;
	t_ipt2	bottom_left;
	t_ipt2	bottom_right;

	top_left.x = 0;
	top_right.x = im -> nx - 1;
	bottom_left.x = 0;
	bottom_right.x = im -> nx - 1;
	top_left.y = 0;
	top_right.y = 0;
	bottom_left.y = im -> ny - 1;
	bottom_right.y = im -> ny - 1;
	draw_line_image(&top_left, &top_right, im);
	draw_line_image(&top_right, &bottom_right, im);
	draw_line_image(&bottom_right, &bottom_left, im);
	draw_line_image(&bottom_left, &top_left, im);
	return ;
}
