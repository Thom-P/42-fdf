/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:41:11 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/11 01:06:42 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Test if can initialize window and draw with minilibx

#include "mlx.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

typedef struct	s_xptr
{
	void	*mlx;
	void	*win;
}				t_xptr;

typedef struct	s_draw
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
}				t_draw;

//void	_draw_hline(void *mlx, void *win, int x_i, int x_f, int y);

void	draw_line(const int p0[2], const int p1[2], t_xptr *t_p);

int		draw_line_sub(int p0_cp[2], const int p1[2], t_draw *t_d, t_xptr *t_p);

int		_key_hook(int keycode, void *t_p);

int	main(void)
{
	
	t_xptr	t_p;
	void	*mlx;
	void	*win;
	int		size_x;
	int		size_y;
	char	*title;

	int x0 = 100;
	int x1 = 400;
	int y0 = 50;
	int y1 = 3000;
	int p0[2] = {x0, y0};
	int p1[2] = {x1, y1};

	title = "My first window!";
	size_x = 500;
	size_y = 250;
	
	mlx = mlx_init();
	if (mlx == NULL)
		return (-1);
	win = mlx_new_window(mlx, size_x, size_y, title);
	if (win == NULL)
		return (-1);
	t_p.mlx = mlx;
	t_p.win = win;
	draw_line(p0, p1, &t_p);
	mlx_pixel_put(mlx, win, x0, y0, 255);
	mlx_pixel_put(mlx, win, x1, y1, 255);

	mlx_key_hook(win, &_key_hook, &t_p);		
	mlx_loop(mlx);
	printf("Never gets here...\n");

	return (0);
}

int	_key_hook(int keycode, void *t_p)
{
	if (keycode == 53)
	{	
		mlx_destroy_window(((t_xptr *)t_p) -> mlx, ((t_xptr *)t_p) -> win);
		exit(0);
	}
	return (0);
}

// Bresenham's line algo using integer computations only
void	draw_line(const int p0[2], const int p1[2], t_xptr *t_p)
{
    t_draw	t_d;
	int		p0_cp[2];

	p0_cp[0] = p0[0];
	p0_cp[1] = p0[1];
	t_d.dx = abs(p1[0] - p0[0]);
	if (p0[0] < p1[0])
		t_d.sx = 1;
	else 
		t_d.sx = -1;
	t_d.dy = -abs(p1[1] - p0[1]);
    if (p0[1] < p1[1])
		t_d.sy = 1;
	else 
		t_d.sy = -1;
    t_d.error = t_d.dx + t_d.dy; 
    while (1)
    {
        if (draw_line_sub(p0_cp, p1, &t_d, t_p))
			break ;
	}
	return ;
}

int	draw_line_sub(int p0_cp[2], const int p1[2], t_draw *t_d, t_xptr *t_p)
{
	int	e2;

	mlx_pixel_put(t_p -> mlx, t_p -> win, p0_cp[0], p0_cp[1], INT_MAX);
	if (p0_cp[0] == p1[0] && p0_cp[1] == p1[1])
		return (1);
	e2 = 2 * t_d -> error;
	if (e2 >= t_d -> dy)
	{   
		if (p0_cp[0] == p1[0])
			return (1);
		t_d -> error = t_d -> error + t_d -> dy;
		p0_cp[0] = p0_cp[0] + t_d -> sx;
	}
	if (e2 <= t_d -> dx)
	{    
		if (p0_cp[1] == p1[1]) 
			return (1);
		t_d -> error = t_d -> error + t_d -> dx;
		p0_cp[1] = p0_cp[1] + t_d -> sy;
	}
	return (0);
}




