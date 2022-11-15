/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:45:44 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/15 09:28:23 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>  //not to remove at the end cause used for perror...
# include <stdlib.h>
# include <limits.h>
# include <math.h> // to replace by -lm flag in gcc?
# include <fcntl.h>

# include "mlx.h"
# include "libft.h"

# include "draw_line.h"

# define ON_DESTROY 17  //closing window event

// Struct for pointers to display session and window
typedef struct	s_xptr
{
	void	*mlx;
	void	*win;
}				t_xptr;

// Struct for 2D int matrix (size m, n)
typedef struct	s_imat
{
	int	m;
	int	n;
	int *imat;
}				t_imat;

// Struct for 2D float matrix (size m, n)
typedef struct	s_fmat
{
	int		m;
	int		n;
	float	*fmat;
}				t_fmat;

//Parsing
t_imat	get_input(char *f_name);

//Debug utils (to remove)
void	print_imat(t_imat imat);

#endif
