/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:45:44 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/20 21:30:02 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>  //used for perror
# include <stdlib.h>
# include <limits.h> // to remove if INT_MAX not used
# include <math.h> // nb: need gcc -lm on Linux?
# include <fcntl.h>

# include "mlx.h"
# include "libft.h"

# define DESTROY_WIN 17  //closing window event
# define KEY_DOWN 2
# define KEY_UP 3

# define ESCAPE_KEY 53
# define MAJ_KEY 257
# define I_KEY 34
# define O_KEY 31
# define K_KEY 40
# define L_KEY 37
# define LEFT_ARROW_KEY 123
# define RIGHT_ARROW_KEY 124
# define DOWN_ARROW_KEY 125
# define UP_ARROW_KEY 126
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2

// Colors
# define WHITE 16777215 //White
# define RED 16711680 //Red
# define GREEN 65280 //Green
# define BLUE 255 //Blue

//# define WIN_NX 1280 //values for macbook pro full screen
//# define WIN_NY 750

# define WIN_NX 1920 //values for AOC screen
# define WIN_NY 1030

//# define WIN_NX 2560 //values for 42 mac
//# define WIN_NY 1395

# define THETA_Z_ISO (45. / 180. * M_PI)
# define THETA_X_ISO  (-(90. - 35.2644) / 180. * M_PI)
	
// Pointers to display session and window
typedef struct	s_xptr
{
	void	*mlx;
	void	*win;
}				t_xptr;

// Mlx_image info
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

// View/transform
typedef struct	s_view
{
	float	theta_z;
	float	theta_x;
	float	d_theta;
	float	zoom;
	float	z_scale;
	int		off_x;
	int		off_y;
	int		d_offset;
}				t_view;

// int point 2D
typedef struct s_ipt2
{
	int	x;
	int	y;
}				t_ipt2;

// int matrix (size m, n)
typedef struct	s_imat
{
	int	m;
	int	n;
	int *imat;
}				t_imat;

// float matrix (size m, n)
typedef struct	s_fmat
{
	int		m;
	int		n;
	float	*fmat;
}				t_fmat;

// Variables for Bresenham's segment tracing algo
typedef struct s_draw
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
}				t_draw;

// Meta-struct of other structs to use in hooks
typedef struct	s_meta
{
	t_fmat		init_fmat;
	t_xptr		xp;
	t_image		im;
	t_view		view;
   	t_imat		data_in;	
}				t_meta;

//main
void	process_and_render(t_meta *meta);

//Parsing
t_imat	get_input(char *f_name);

//Processing
void	create_init_fmat(t_imat *data_in, t_fmat *init_fmat, t_image *im);
void	transform_fmat(t_fmat *fmat, t_view *view);
int		*proj_shift(t_fmat *fmat, t_meta *meta, int **is_in_im);

//Drawing
void	draw_line_image(t_ipt2 *p0, t_ipt2 *p1, t_image *im);
void	draw_grid_image(int *proj_mat, int *is_in_im, t_image *im, t_imat *data_in);
void	draw_box_around_image(t_image *im);

//Hooks
int	key_down_hook(int keycode, t_meta *meta);
int	key_up_hook(int keycode, t_meta *meta);
int	destroy_hook(t_meta *meta);

//Matrix utils
t_fmat fmat_dup(t_fmat *fmat_in);
void premult_fmat(t_fmat *B, t_fmat *A);

//Mem utils
void	free_word_arr(char **word_arr, int n);
void	free_fmats_exit(float *fmat, float *init_fmat);

//Debug utils (to remove)
void	print_imat(t_imat imat);
void	print_fmat(t_fmat fmat);

#endif
