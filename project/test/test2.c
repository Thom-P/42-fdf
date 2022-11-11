/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:59:19 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/11 15:41:14 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Test if can initialize window and draw with minilibx

#include "mlx.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

#include "../source/draw_line.h"
#include "../source/draw_line.c"

typedef struct	s_xptr
{
	void	*mlx;
	void	*win;
}				t_xptr;

int		_key_hook(int keycode, void *t_p);

void	_draw_buffer(t_buffer *t_buff, t_xptr *t_xp);

int	main(void)
{
	
	t_xptr	t_xp;
	void	*mlx;
	void	*win;
	int		size_x;
	int		size_y;
	char	*title;
	
	title = "My first window!";
	size_x = 1800;
	size_y = 1000;

	//void	*im;
	int x0 = 800;
	int x1 = 200;
	int y0 = 50;
	int y1 = 400;
	int	nx = 1000;
	int ny = 500;

	//int buff[ny][nx] = {0};
	int *buff;
	buff = (int *)calloc(ny * nx, sizeof(int));

	t_buffer t_buff;

	t_pt2d	t_p0;
	t_pt2d	t_p1;

	t_buff.nx = nx;
	t_buff.ny = ny;
	t_buff.buff = buff;
	t_p0.x = x0;
	t_p1.x = x1;
	t_p0.y = y0;
	t_p1.y = y1;
		
	mlx = mlx_init();
	if (mlx == NULL)
		return (-1);
	win = mlx_new_window(mlx, size_x, size_y, title);
	if (win == NULL)
		return (-1);
	t_xp.mlx = mlx;
	t_xp.win = win;
	
	//void *mlx_new_image(void *mlx_ptr, int width, int height);
	//im = mlx_new_image(mlx, int width, int height);

	draw_line_buff(&t_p0, &t_p1, &t_buff);
	_draw_buffer(&t_buff, &t_xp);
	mlx_pixel_put(mlx, win, x0, y0, 255);
	mlx_pixel_put(mlx, win, x1, y1, 255);

	mlx_key_hook(win, &_key_hook, &t_xp);		
	mlx_loop(mlx);
	printf("Never gets here...\n");

	return (0);
}

int	_key_hook(int keycode, void *t_xp)
{
	if (keycode == 53)
	{	
		mlx_destroy_window(((t_xptr *)t_xp) -> mlx, ((t_xptr *)t_xp) -> win);
		exit(0);
	}
	return (0);
}

void	_draw_buffer(t_buffer *t_buff, t_xptr *t_xp)
//to be replaced by put_image later
{
	int	xx;
	int	yy;
	int color;

	yy = 0;
	while (yy < t_buff -> ny)
	{
		xx = 0;
		while (xx < t_buff -> nx)
		{
			color = (t_buff -> buff)[yy * t_buff -> nx + xx];
			if (color > 0)
				mlx_pixel_put(t_xp -> mlx, t_xp -> win, xx, yy, color);
			xx++;
		}
		yy++;
	}
	return ;
}
