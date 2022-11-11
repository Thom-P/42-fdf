/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:38:30 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/11 17:09:22 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_LINE_H
# define DRAW_LINE_H

# include <stdlib.h>
# include <limits.h>

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

#endif
