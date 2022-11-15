/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:44:28 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/15 15:41:30 by tplanes          ###   ########.fr       */
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

	// Processing
	
	t_fmat	init_mat;

	nx = data_in.n;
	ny = data_in.m;
	create_init_mat(&data_in, &init_mat);
	//rotate_mat
	
	// rendering
	
	t_xptr	xp;
	int		win_nx;
	int		win_ny;

	win_nx = 1280; //values for macbook pro full screen
	win_ny = 750;

	create_win(&xp, win_ny, win_nx, "***Fil de Fer***");

	/*t_pt2d	p0;
	t_pt2d	p1;

	p0.x = 600;
	p1.x = 400;
	p0.y = 400;
	p1.y = 200;*/

	//t_image	buff; //for later to avoid screen tearing
	t_image	im;

	im.nx = floor(0.75 * win_nx);
	im.ny = floor(0.75 * win_ny);
	im.id = mlx_new_image(xp.mlx, im.nx, im.ny);
	im.addr = mlx_get_data_addr(im.id, &im.bpp, &im.line_size, &im.endian);
	
	draw_grid_image(&init_mat, &im, &data_in); //data in passed only for dimensions (only mat freed)
	//draw_line_image(&p0, &p1, &im);
	mlx_put_image_to_window(xp.mlx, xp.win, im.id, 0, 0);
	
	//mlx_pixel_put(xp.mlx, xp.win, p0.x, p0.y, 255);
	//mlx_pixel_put(xp.mlx, xp.win, p1.x, p1.y, 255);

	mlx_key_hook(xp.win, &_key_hook, &xp);
    mlx_hook(xp.win, ON_DESTROY, 0, &_destroy_hook, &xp);	
	
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
	if (keycode == 53)
	{	
		mlx_destroy_window(((t_xptr *)xp) -> mlx, ((t_xptr *)xp) -> win);
		exit(0);
	}
	return (0);
}

//called when closing window from clicking cross (ON_DESTROY event)
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

/*void	_draw_buffer(t_buffer *buffer, t_xptr *xp)
//to be replaced by put_image later
{
	int	xx;
	int	yy;
	int color;

	yy = 0;
	while (yy < buffer -> ny)
	{
		xx = 0;
		while (xx < buffer -> nx)
		{
			color = (buffer -> buff)[yy * buffer -> nx + xx];
			if (color > 0)
				mlx_pixel_put(xp -> mlx, xp -> win, xx, yy, color);
			xx++;
		}
		yy++;
	}
	return ;
}*/
