/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:35:19 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/12 14:04:36 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	_put_pix(t_pt2d *p0, t_pt2d *p1, t_draw *d, t_buffer *buffer);

// Bresenham's line algo using integer computations only
void	draw_line_buff(t_pt2d *p0, t_pt2d *p1, t_buffer *buffer)
//nb: could add in box check for p1 and p0
{
	t_draw	d;
	t_pt2d	p0_cpy;

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
		if (_put_pix(&p0_cpy, p1, &d, buffer))
			break ;
	}
	return ;
}

// copy of t_p0 is provided so that point is not modified during draw
int	_put_pix(t_pt2d *p0, t_pt2d *p1, t_draw *d, t_buffer *buffer)
{
	int	e2;

	(buffer -> buff)[(p0 -> y) * (buffer -> nx) + p0 -> x] = INT_MAX;
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
