/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:44:28 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/19 12:07:50 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_verify_arguments(int ac, char **av);

static void	_create_win(t_xptr *xp, int win_ny, int win_nx, char *title);

static void	_create_image(t_xptr *xp, t_image *im);

//print_imat(meta.data_in);	
//print_fmat(meta.init_fmat);
int	main(int ac, char **av)
{
	t_meta	meta;

	_verify_arguments(ac, av);
	meta.data_in = get_input(av[1]);
	_create_win(&meta.xp, WIN_NY, WIN_NX, "***Fil de Fer***");
	_create_image(&meta.xp, &meta.im);
	create_init_fmat(&meta.data_in, &meta.init_fmat, &meta.im);
	meta.view.theta_z = THETA_Z_ISO;
	meta.view.theta_x = THETA_X_ISO;
	meta.view.zoom = 1;
	meta.view.z_scale = 1;
	meta.view.d_theta = M_PI / 20;	
	meta.view.off_x = 0;
	meta.view.off_y = 0;
	process_and_render(&meta);
	mlx_hook(meta.xp.win, KEY_DOWN, 0, &key_down_hook, &meta);
	mlx_hook(meta.xp.win, KEY_UP, 0, &key_up_hook, &meta);
	mlx_hook(meta.xp.win, DESTROY_WIN, 0, &destroy_hook, &meta.xp);
	mlx_loop(meta.xp.mlx);
	return (0);
}

//dup init mat to always start back from init state and not prop error
//nb: put data_in sizes in indep struct to avoid carrying data_in around?
//apply zoom (eg +/- ?)  do both directly in proj op?
//apply shift (arrows /maj for small)//need to free init ma
//data in passed only for dimensions (only mat freed)t at closure?
//replace destr and creat by a ima_clean fct to reset pix?
void	process_and_render(t_meta *meta)
{
	t_fmat	fmat;
	int		*proj_mat;
	//add bool arr var here? as well as links to neighbs?

	fmat = fmat_dup(&meta -> init_fmat);
	transform_fmat(&fmat, &meta -> view);
	
	proj_mat = proj_shift(&fmat, &meta -> im, &meta -> view);
	free(fmat.fmat);
	draw_grid_image(proj_mat, &meta -> im, &meta -> data_in);
	free(proj_mat);
	mlx_put_image_to_window(meta -> xp.mlx, meta -> xp.win,
		meta -> im.id, meta -> im.pos_x, meta -> im.pos_y);
	mlx_string_put(meta -> xp.mlx, meta -> xp.win, 1, 1, BLUE, "Test blablabla");
	mlx_destroy_image(meta -> xp.mlx, meta -> im.id);
	_create_image(&meta -> xp, &meta -> im);
	return ;
}

static void	_verify_arguments(int ac, char **av)
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

static void	_create_win(t_xptr *xp, int win_ny, int win_nx, char *title)
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

static void	_create_image(t_xptr *xp, t_image *im)
{
	im -> nx = round(0.9 * WIN_NX);
	im -> ny = round(0.9 * WIN_NY);
	im -> pos_x = round(0.5 * (WIN_NX - im -> nx));
	im -> pos_y = round(0.5 * (WIN_NY - im -> ny));
	im -> id = mlx_new_image(xp -> mlx, im -> nx, im -> ny);
	im -> addr = mlx_get_data_addr(im -> id, &im -> bpp,
			&im -> line_size, &im -> endian);
	draw_box_around_image(im);
	return ;
}
