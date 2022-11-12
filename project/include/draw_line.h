/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:38:30 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/12 14:16:06 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_LINE_H
# define DRAW_LINE_H

typedef struct s_pt2d
{
	int	x;
	int	y;
}				t_pt2d;

typedef struct s_buffer
{
	int	nx;
	int	ny;
	int	*buff;
}				t_buffer;

typedef struct s_draw
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
}				t_draw;

void	draw_line_buff(t_pt2d *p0, t_pt2d *p1, t_buffer *buffer);

#endif
