/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:44:28 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/17 15:24:10 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	_verify_arguments(int ac, char **av);

int		_key_hook(int keycode, void *t_p);

int		_destroy_hook(void *xp);

//int		_loop_hook(void *xp);

void	create_win(t_xptr *xp, int win_ny, int win_nx, char *title);

void 	create_image(t_xptr *xp, t_image *im);

int	main(int ac, char **av)
{
	//Parsing
	t_imat	data_in;
	
	_verify_arguments(ac, av);		
	data_in = get_input(av[1]);
	//print_imat(data_in);	

	//Create window and image and buff
	
	t_xptr	xp;
	t_image	im;
	//t_image	buff; //for later to avoid screen tearing?

	create_win(&xp, WIN_NY, WIN_NX, "***Fil de Fer***");
	create_image(&xp, &im);
	
	// Processing
	
	t_fmat	init_fmat; // the unrotated one
	create_init_fmat(&data_in, &init_fmat, &im);
	//fprintf(stderr, "init float mat created\n");	
	//print_fmat(init_fmat);
	
	//rotate_mat (eg ctrl + arrow (+ maj for small ones))
	
	float theta_z;
	theta_z = 45. / 180. * M_PI;
	float theta_x;
	theta_x = - 1. * (90. - 35.2644) / 180. * M_PI;
	
	rotate_fmat(&init_fmat, theta_z, theta_x);

	//apply zoom (eg +/- ?)  do both directly in proj op?
	//apply shift (arrows /maj for small)

	// rendering

	//t_fmat fmat_dup(t_fmat *fmat_in)

	draw_grid_image(&init_fmat, &im, &data_in); //data in passed only for dimensions (only mat freed)
	mlx_put_image_to_window(xp.mlx, xp.win, im.id, im.pos_x, im.pos_y);

	mlx_key_hook(xp.win, &_key_hook, &xp);
    mlx_hook(xp.win, DESTROY_WIN, 0, &_destroy_hook, &xp);	
	
	mlx_loop(xp.mlx);
	//never gets here
	return (0);
}

void	_verify_arguments(int ac, char **av)
{	
	ft_putstr_fd("Starting Fil de Fer...\n", 1);
	if (ac != 2)
	{
		ft_putstr_fd("Incorrect number of arguments (expected 1).\n", 1);
		exit (EXIT_FAILURE);
	}
	ft_putstr_fd("Loading ", 1);
	ft_putstr_fd(av[1], 1);
	ft_putstr_fd("...\n", 1);
	return ;
}	

void	create_win(t_xptr *xp, int win_ny, int win_nx, char *title)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (mlx == NULL)
		exit(-1);
	win = mlx_new_window(mlx, win_nx, win_ny, title);
	if (win == NULL)
		exit(-1);
	xp -> mlx = mlx;
	xp -> win = win;
	return ;
}

void create_image(t_xptr *xp, t_image *im)
{
	im -> nx = round(0.9 * WIN_NX);
	im -> ny = round(0.9 * WIN_NY);
	im -> pos_x = round(0.5 * (WIN_NX - im -> nx));
	im -> pos_y = round(0.5 * (WIN_NY - im -> ny));
	im -> id = mlx_new_image(xp -> mlx, im -> nx, im -> ny);
	im -> addr = mlx_get_data_addr(im -> id, &im -> bpp, &im -> line_size, &im -> endian);
	draw_box_around_image(im);
	return ;
}

int	_key_hook(int keycode, void *xp)
{
	if (keycode == ESCAPE_KEY)
	{	
		mlx_destroy_window(((t_xptr *)xp) -> mlx, ((t_xptr *)xp) -> win);
		exit(0);
	}
	return (0);
}

//called when closing window from clicking cross (DESTROY_WIN event)
int	_destroy_hook(void *xp)
{
	mlx_destroy_window(((t_xptr *)xp) -> mlx, ((t_xptr *)xp) -> win);
	exit(0);
	return (0);
}
