/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:35:19 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/11 17:06:23 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_line.h"

int	_draw_pix_buff(t_pt2d *t_p0, t_pt2d *t_p1, t_draw *t_d, t_buffer *t_buff);

// Bresenham's line algo using integer computations only
void	draw_line_buff(t_pt2d *t_p0, t_pt2d *t_p1, t_buffer *t_buff)
//nb: could add in box check for p1 and p0
{
	t_draw	t_d;
	t_pt2d	t_p0_cpy;

	t_p0_cpy.x = t_p0 -> x;
	t_p0_cpy.y = t_p0 -> y;
	t_d.dx = abs(t_p1 -> x - t_p0 -> x);
	if (t_p0 -> x < t_p1 -> x)
		t_d.sx = 1;
	else
		t_d.sx = -1;
	t_d.dy = -abs(t_p1 -> y - t_p0 -> y);
	if (t_p0 -> y < t_p1 -> y)
		t_d.sy = 1;
	else
		t_d.sy = -1;
	t_d.error = t_d.dx + t_d.dy;
	while (1)
	{
		if (_draw_pix_buff(&t_p0_cpy, t_p1, &t_d, t_buff))
			break ;
	}
	return ;
}

// copy of t_p0 is provided so that point is not modified during draw
int	_draw_pix_buff(t_pt2d *t_p0, t_pt2d *t_p1, t_draw *t_d, t_buffer *t_buff)
{
	int	e2;

	(t_buff -> buff)[(t_p0 -> y) * (t_buff -> nx) + t_p0 -> x] = INT_MAX;
	if (t_p0 -> x == t_p1 -> x && t_p0 -> y == t_p1 -> y)
		return (1);
	e2 = 2 * t_d -> error;
	if (e2 >= t_d -> dy)
	{
		if (t_p0 -> x == t_p1 -> x)
			return (1);
		t_d -> error += t_d -> dy;
		t_p0 -> x += t_d -> sx;
	}
	if (e2 <= t_d -> dx)
	{
		if (t_p0 -> y == t_p1 -> y)
			return (1);
		t_d -> error += t_d -> dx;
		t_p0 -> y += t_d -> sy;
	}
	return (0);
}
