/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:18:28 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/20 14:59:46 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		_get_next_pix(t_ipt2 *p0, t_ipt2 *p1, t_draw *d);

void			_put_pix_image(t_image *im, int x, int y, int color);

int				*proj_shift(t_fmat *fmat, t_image *im, t_view *view, int **is_in_im);

static void	_draw_edge_right(int *proj_mat, int cc, t_imat *data_in, t_image *im);

static void	_draw_edge_down(int *proj_mat, int cc, t_imat *data_in, t_image *im);

void	draw_grid_image(int *proj_mat, int *is_in_im, t_image *im, t_imat *data_in)
{
	int		i;
	int 	j;
	int		cc;

	cc = 0;
	while (cc < data_in -> m * data_in -> n)
	{
		if (!is_in_im[cc])
		{	
			cc++;
			continue ;
		}
		i = cc / data_in -> n;
		j = cc % data_in -> n;
		if (j < data_in -> n - 1  && is_in_im[cc + 1])
			_draw_edge_right(proj_mat, cc, data_in, im);
		if (i < data_in -> m - 1 && is_in_im[cc + data_in -> n])
			_draw_edge_down(proj_mat, cc, data_in, im);
		cc++;
	}
	return ;
}

static void	_draw_edge_right(int *proj_mat, int cc, t_imat *data_in, t_image *im)
{	
	int nb_pts;
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

static void	_draw_edge_down(int *proj_mat, int cc, t_imat *data_in, t_image *im)
{	
	int nb_pts;
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

void draw_box_around_image(t_image *im)
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

// Bresenham's line algo using integer computations only
void	draw_line_image(t_ipt2 *p0, t_ipt2 *p1, t_image *im)
//nb: could add in box check for p1 and p0
{
	t_draw	d;
	t_ipt2	p0_cpy;

	p0_cpy.x = p0 -> x;
	p0_cpy.y = p0 -> y;
	d.dx = abs(p1 -> x - p0 -> x);
	if (p0 -> x < p1 -> x)
		d.sx = 1;
	else
		d.sx = -1;
	d.dy = -abs(p1 -> y - p0 -> y);
	if (p0 -> y < p1 -> y)
		d.sy = 1;
	else
		d.sy = -1;
	d.error = d.dx + d.dy;
	while (1)
	{
		_put_pix_image(im, p0_cpy.x, p0_cpy.y, WHITE);
		if (_get_next_pix(&p0_cpy, p1, &d))
			break ;
	}
	return ;
}

// copy of t_p0 is provided so that point is not modified during draw
static int	_get_next_pix(t_ipt2 *p0, t_ipt2 *p1, t_draw *d)
{
	int	e2;

	if (p0 -> x == p1 -> x && p0 -> y == p1 -> y)
		return (1);
	e2 = 2 * d -> error;
	if (e2 >= d -> dy)
	{
		if (p0 -> x == p1 -> x)
			return (1);
		d -> error += d -> dy;
		p0 -> x += d -> sx;
	}
	if (e2 <= d -> dx)
	{
		if (p0 -> y == p1 -> y)
			return (1);
		d -> error += d -> dx;
		p0 -> y += d -> sy;
	}
	return (0);
}

void	_put_pix_image(t_image *im, int x, int y, int color)
// Only works for 4 bytes = 32 bit depth ? Could dev a byte wise method...
{
	char	*pix_addr;

	pix_addr = im -> addr + y * im -> line_size + x * (im -> bpp / 8);
	//fprintf(stderr, "%p %i\n", pix_addr, color);
	*((unsigned int *)pix_addr) = color;
	return ;
}
