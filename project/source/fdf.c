/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:44:28 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/27 15:44:47 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_init_view(t_view *view, t_image *im);

static void	_create_win(t_meta *meta, int win_ny, int win_nx, char *title);

static void	_create_image(t_meta *meta, t_image *im);

int	main(int ac, char **av)
{
	t_meta	meta;
	char	*str;

	if (ac != 2)
	{
		ft_putstr_fd("Incorrect number of arguments (expected 1).\n", 1);
		exit (EXIT_FAILURE);
	}
	meta.data_in = get_input(av[1]);
	init_colors(&meta.data_in, &meta.view);
	_create_win(&meta, WIN_NY, WIN_NX, "***Fil de Fer***");
	str = "Reset iso: R, Move: WASD, (Slow) Rotate: (SHIFT) ARROWS, "
		"Zoom In/Out: I/O, Z-scale +/-/Auto: K/L/Z, Colors: SPACE, Quit: ESC";
	mlx_string_put(meta.xp.mlx, meta.xp.win, 1, 1, WHITE, str);
	_create_image(&meta, &meta.im);
	create_init_fmat(&meta.data_in, &meta.init_fmat, &meta.im);
	free(meta.data_in.imat);
	meta.curr_fmat = fmat_dup(&meta.init_fmat);
	_init_view(&meta.view, &meta.im);
	process_and_render(&meta);
	mlx_hook(meta.xp.win, KEY_DOWN, 0, &key_down_hook, &meta);
	mlx_hook(meta.xp.win, KEY_UP, 0, &key_up_hook, &meta);
	mlx_hook(meta.xp.win, DESTROY_WIN, 0, &destroy_hook, &meta);
	mlx_loop(meta.xp.mlx);
	return (0);
}

void	process_and_render(t_meta *meta)
{
	t_fmat	*fmat;
	int		*proj_mat;
	int		*is_in_im;	

	fmat = &meta -> curr_fmat;
	transform_fmat(fmat, &meta -> init_fmat, &meta -> view);
	proj_mat = proj_shift(fmat, meta, &is_in_im);
	draw_grid_image(proj_mat, is_in_im, meta);
	free(proj_mat);
	free(is_in_im);
	draw_box_around_image(&meta -> im);
	mlx_put_image_to_window(meta -> xp.mlx, meta -> xp.win,
		meta -> im.id, meta -> im.pos_x, meta -> im.pos_y);
	mlx_destroy_image(meta -> xp.mlx, meta -> im.id);
	_create_image(meta, &meta -> im);
	return ;
}

// Initialize view params (incl. isometric angles)
static void	_init_view(t_view *view, t_image *im)
{
	view -> theta_z = 45. / 180. * M_PI;
	view -> theta_x = -(90. - 35.2644) / 180. * M_PI;
	view -> zoom = 1;
	view -> z_scale = 1;
	view -> d_theta = M_PI / 20;
	view -> off_x = 0;
	view -> off_y = 0;
	view -> d_offset = round(im -> nx / 20);
	view -> i_cmap = 0;
	return ;
}

static void	_create_win(t_meta *meta, int win_ny, int win_nx, char *title)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (mlx == NULL)
	{	
		free(meta -> data_in.imat);
		free(meta -> view.i_color);
		exit(EXIT_FAILURE);
	}
	win = mlx_new_window(mlx, win_nx, win_ny, title);
	if (win == NULL)
	{	
		free(meta -> data_in.imat);
		free(meta -> view.i_color);
		exit(EXIT_FAILURE);
	}
	meta -> xp.mlx = mlx;
	meta -> xp.win = win;
	return ;
}

static void	_create_image(t_meta *meta, t_image *im)
{
	im -> nx = round(0.9 * WIN_NX);
	im -> ny = round(0.9 * WIN_NY);
	im -> pos_x = round(0.5 * (WIN_NX - im -> nx));
	im -> pos_y = round(0.5 * (WIN_NY - im -> ny));
	im -> id = mlx_new_image(meta -> xp.mlx, im -> nx, im -> ny);
	if (im -> id == NULL)
	{
		free(meta -> data_in.imat);
		free(meta -> view.i_color);
		mlx_destroy_window(meta -> xp.mlx, meta -> xp.win);
		exit(EXIT_FAILURE);
	}
	im -> addr = mlx_get_data_addr(im -> id, &im -> bpp,
			&im -> line_size, &im -> endian);
	return ;
}
