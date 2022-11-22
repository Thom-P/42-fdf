/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:10:51 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/22 14:05:26 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	_get_next_pix(t_ipt2 *p0, t_ipt2 *p1, t_draw *d);

static void	_put_pix_image(t_image *im, int x, int y, int color);

// Bresenham's line algo using integer computations only
void	draw_line_image(t_ipt2 *p0, t_ipt2 *p1, t_image *im, int color)
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
		_put_pix_image(im, p0_cpy.x, p0_cpy.y, color);
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
	*((unsigned int *)pix_addr) = color;
	return ;
}
