/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:44:28 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/15 09:57:20 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		_key_hook(int keycode, void *t_p);

int		_destroy_hook(void *xp);

//int		_loop_hook(void *xp);

void	_draw_buffer(t_buffer *buffer, t_xptr *xp);

void	create_win(t_xptr *xp, int win_ny, int win_nx, char *title);

int	main(int ac, char **av)
{
	t_xptr	xp;
	int		win_nx;
	int		win_ny;
	t_buffer buffer;
	int		*buff;
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

	win_nx = 1280; //values for macbook pro full screen
	win_ny = 750;
	buffer.nx = floor(0.75 * win_nx);
	buffer.ny = floor(0.75 * win_ny);
	buff = (int *)ft_calloc(buffer.ny * buffer.nx, sizeof(int));
	buffer.buff = buff;

	create_win(&xp, win_ny, win_nx, "***Fil de Fer***");

	t_pt2d	p0;
	t_pt2d	p1;

	p0.x = 600;
	p1.x = 400;
	p0.y = 400;
	p1.y = 200;
		

	void	*im_ptr;
	char 	*im_buff;
	int 	*bits_per_pixel;
	int		*size_line;
	int		*endian;

	im_ptr = mlx_new_image(mlx, buffer.nx, buffer.ny);
	im_buff = mlx_get_data_addr(im_ptr, bits_per_pixel, size_line, endian);

	//draw_line_buff(&p0, &p1, &buffer);
	//_draw_buffer(&buffer, &xp);
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

void	_draw_buffer(t_buffer *buffer, t_xptr *xp)
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
}
