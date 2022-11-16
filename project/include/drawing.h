/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:19:30 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/16 10:20:04 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

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
