/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:18:28 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/26 14:01:09 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_draw_edge_r(int *proj_mat, int cc, t_meta *meta, int *cmap);

static void	_draw_edge_d(int *proj_mat, int cc, t_meta *meta, int *cmap);

void	draw_grid_image(int *proj_mat, int *in_im, t_meta *meta)
{
	int	i;
	int	j;
	int	cc;
	int	*cmap;

	cmap = &meta -> view.cmaps[meta -> view.i_cmap][0];
	cc = 0;
	while (cc < meta -> data_in.m * meta -> data_in.n)
	{
		if (!in_im[cc])
		{	
			cc++;
			continue ;
		}
		i = cc / meta -> data_in.n;
		j = cc % meta -> data_in.n;
		if (j < meta -> data_in.n - 1 && in_im[cc + 1])
			_draw_edge_r(proj_mat, cc, meta, cmap);
		if (i < meta -> data_in.m - 1 && in_im[cc + meta -> data_in.n])
			_draw_edge_d(proj_mat, cc, meta, cmap);
		cc++;
	}
	return ;
}

static void	_draw_edge_r(int *proj_mat, int cc, t_meta *meta, int *cmap)
{	
	int		nb_pts;
	t_ipt2	p;
	t_ipt2	p_right;
	int		*i_color;
	int		color;

	i_color = meta -> view.i_color;
	color = cmap[(int)round(0.5 * (i_color[cc] + i_color[cc + 1]))];
	nb_pts = meta -> data_in.m * meta -> data_in.n;
	p.x = proj_mat[cc];
	p.y = proj_mat[cc + nb_pts];
	p_right.x = proj_mat[cc + 1];
	p_right.y = proj_mat[cc + 1 + nb_pts];
	draw_line_image(&p, &p_right, &meta -> im, color);
	return ;
}

static void	_draw_edge_d(int *proj_mat, int cc, t_meta *meta, int *cmap)
{	
	int		nb_pts;
	t_ipt2	p;
	t_ipt2	p_down;
	int		*i_color;
	int		color;

	i_color = meta -> view.i_color;
	color = cmap[(int)round(0.5
			* (i_color[cc] + i_color[cc + meta -> data_in.n]))];
	nb_pts = meta -> data_in.m * meta -> data_in.n;
	p.x = proj_mat[cc];
	p.y = proj_mat[cc + nb_pts];
	p_down.x = proj_mat[cc + meta -> data_in.n];
	p_down.y = proj_mat[cc + meta -> data_in.n + nb_pts];
	draw_line_image(&p, &p_down, &meta -> im, color);
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
	draw_line_image(&top_left, &top_right, im, WHITE);
	draw_line_image(&top_right, &bottom_right, im, WHITE);
	draw_line_image(&bottom_right, &bottom_left, im, WHITE);
	draw_line_image(&bottom_left, &top_left, im, WHITE);
	return ;
}
/*
Removed because slower than destroy and create new image...
// Reset each image byte to zero 
void	reset_image_black(t_image *im)
{
	int	i;

	i = 0;
	while (i < im -> ny * im -> line_size)
		*(im -> addr + i++) = 0;
	return ;
}
*/
