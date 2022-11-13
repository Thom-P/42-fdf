/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:45:44 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/13 13:26:42 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>  //to remove at the end
# include <stdlib.h>
# include <limits.h>
# include <math.h>

# include "mlx.h"
# include "libft.h"

# include "draw_line.h"

// Struct for pointers to display session and window
typedef struct	s_xptr
{
	void	*mlx;
	void	*win;
}				t_xptr;

#endif
