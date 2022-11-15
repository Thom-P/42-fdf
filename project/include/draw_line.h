/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:38:30 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/15 16:50:12 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_LINE_H
# define DRAW_LINE_H

typedef struct s_pt2d
{
	int	x;
	int	y;
}				t_pt2d;

typedef struct s_draw
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
}				t_draw;

void	draw_line_image(t_pt2d *p0, t_pt2d *p1, t_image *im);

void	draw_grid_image(t_fmat *init_mat, t_image *im, t_imat *data_in);

#endif
