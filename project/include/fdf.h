/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:45:44 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/17 12:33:27 by tplanes          ###   ########.fr       */
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

# define DESTROY_WIN 17  //closing window event
# define ESCAPE_KEY 53

//# define WIN_NX 1280 //values for macbook pro full screen
//# define WIN_NY 750

# define WIN_NX 2560 //values for 42 mac
# define WIN_NY 1395

// Struct for pointers to display session and window
typedef struct	s_xptr
{
	void	*mlx;
	void	*win;
}				t_xptr;

// Struct for mlx_image info
typedef struct	s_image
{
	void	*id;
	char 	*addr;
	int 	bpp;
	int		line_size;
	int		endian;
	int		nx;
	int		ny;
	int		pos_x;
	int		pos_y;
}				t_image;

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

//Processing
void	create_init_fmat(t_imat *data_in, t_fmat *init_fmat, t_image *im);
void	rotate_fmat(t_fmat *fmat, float theta_z, float theta_x);

//Drawing
# include "drawing.h"

//Matrix utils
t_fmat fmat_dup(t_fmat *fmat_in);
void premult_fmat(t_fmat *B, t_fmat *A);

//Debug utils (to remove)
void	print_imat(t_imat imat);
void	print_fmat(t_fmat fmat);

#endif
