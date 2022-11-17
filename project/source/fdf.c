/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:44:28 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/17 12:37:47 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		_key_hook(int keycode, void *t_p);

int		_destroy_hook(void *xp);

//int		_loop_hook(void *xp);

void	create_win(t_xptr *xp, int win_ny, int win_nx, char *title);

int	main(int ac, char **av)
{
	//Parsing
	t_imat	data_in;
	
	ft_putstr_fd("Starting Fdf...\n", 1);
	if (ac != 2)
	{
		ft_putstr_fd("Incorrect number of arguments (expected 1).\n", 1);
		return (-1);
	}
	ft_putstr_fd(av[1], 1);
	ft_putchar_fd('\n', 1);
	data_in = get_input(av[1]);
	print_imat(data_in);	

	// Initiate win/image params (needed for scaling processing)
	//t_image	buff; //for later to avoid screen tearing
	t_image	im;

	im.nx = round(0.9 * WIN_NX);
	im.ny = round(0.9 * WIN_NY);
	im.pos_x = round(0.5 * (WIN_NX - im.nx));
	im.pos_y = round(0.5 * (WIN_NY - im.ny));
	
	// Processing
	
	t_fmat	init_fmat; // the unrotated one

	create_init_fmat(&data_in, &init_fmat, &im);
	//fprintf(stderr, "init float mat created\n");	
	//print_fmat(init_fmat);
	//exit(0);
	
	//rotate_mat (eg ctrl + arrow (+ maj for small ones))
	
	float theta_z;
	theta_z = 45. / 180. * M_PI;
	float theta_x;
	theta_x = - 1. * (90. - 35.3) / 180. * M_PI;
	
	rotate_fmat(&init_fmat, theta_z, theta_x);

	//apply zoom (eg +/- ?)  do both directly in proj op?
	//apply shift (arrows /maj for small)

	// rendering
	
	t_xptr	xp;
	
	create_win(&xp, WIN_NY, WIN_NX, "***Fil de Fer***");

	im.id = mlx_new_image(xp.mlx, im.nx, im.ny);
	im.addr = mlx_get_data_addr(im.id, &im.bpp, &im.line_size, &im.endian);
	
	draw_box_around_image(&im); //draw a box around the image to see its size while testing

	draw_grid_image(&init_fmat, &im, &data_in); //data in passed only for dimensions (only mat freed)
	
	mlx_put_image_to_window(xp.mlx, xp.win, im.id, im.pos_x, im.pos_y);

	mlx_key_hook(xp.win, &_key_hook, &xp);
    mlx_hook(xp.win, DESTROY_WIN, 0, &_destroy_hook, &xp);	
	
	//mlx_loop_hook(mlx, &_loop_hook, &xp); //needed?
	mlx_loop(xp.mlx);
	printf("Never gets here...\n");

	return (0);
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

/*int _loop_hook(void *xp)
{
	//do what?
	return (0);
}*/
