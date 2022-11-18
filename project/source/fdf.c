/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:44:28 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/18 17:36:37 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	_verify_arguments(int ac, char **av);

int		_key_hook(int keycode, t_meta *meta);

int		_destroy_hook(void *xp);

void	create_win(t_xptr *xp, int win_ny, int win_nx, char *title);

void 	create_image(t_xptr *xp, t_image *im);

void	process_and_render(t_meta *meta);

int	main(int ac, char **av)
{
	t_meta	meta;

	_verify_arguments(ac, av);		
	meta.data_in = get_input(av[1]);
	//print_imat(meta.data_in);	
	create_win(&meta.xp, WIN_NY, WIN_NX, "***Fil de Fer***");
	create_image(&meta.xp, &meta.im);
	
	create_init_fmat(&meta.data_in, &meta.init_fmat, &meta.im);
	//print_fmat(meta.init_fmat);
	
	meta.view.theta_z = THETA_Z_ISO;
	meta.view.theta_x = THETA_X_ISO;

	process_and_render(&meta);
	
	// hooks
	//mlx_key_hook(xp.win, &_key_hook, &meta);
    mlx_hook(meta.xp.win, 2, 0, &_key_hook, &meta); //key_down	
    
	mlx_hook(meta.xp.win, DESTROY_WIN, 0, &_destroy_hook, &meta.xp);	
	mlx_loop(meta.xp.mlx);
	//never gets here
	return (0);
}


// dup init mat to always start back from init state and not prop error
//nb: put data_in sizes in indep struct to avoid carrying data_in around?
//apply zoom (eg +/- ?)  do both directly in proj op?
//apply shift (arrows /maj for small)
void	process_and_render(t_meta *meta)
{
	t_fmat fmat;

	fmat = fmat_dup(&meta -> init_fmat); //need to free init at closure?
	rotate_fmat(&fmat, meta -> view.theta_z, meta -> view.theta_x);
	draw_grid_image(&fmat, &meta -> im, &meta -> data_in); //data in passed only for dimensions (only mat freed)
	free(fmat.fmat);
	mlx_put_image_to_window(meta -> xp.mlx, meta -> xp.win, meta -> im.id, meta -> im.pos_x, meta -> im.pos_y);
	mlx_destroy_image(meta -> xp.mlx, meta -> im.id); //replace destr and creat by a ima_clean fct to reset pix?
	create_image(&meta -> xp, &meta -> im);
	return ;
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

int	_key_hook(int keycode, t_meta *meta)
{
	
	t_xptr	*xp;
	t_view	*view;
	float d_theta;

	d_theta = M_PI / 20;
	//xp = ((t_meta *)meta) -> xp; 
	xp = &meta -> xp; 
	if (keycode == ESCAPE_KEY)
	{	
		mlx_destroy_window(xp -> mlx, xp -> win);
		exit(0);
	}
	/*if (keycode == 257) //MAJ
	{
		if (d_theta == 
	}*/
	
	//fprintf(stderr, "%i\n", keycode);
	//view = ((t_meta *)meta) -> view; //nb will need rotation from current pos, not init_mat
	view = &meta -> view; //nb will need rotation from current pos, not init_mat
	if (keycode < 123 || keycode > 126)
	   return (0);	
	if (keycode == 123) //left arr (will need y axis rot implement..., use z for the moment)
		view -> theta_z -= d_theta;
	if (keycode == 124) //right arr (will need y axis rot implement..., use z for the moment)
		view -> theta_z += d_theta;
	if (keycode == 126) //up arr (rot on x)
		view -> theta_x += d_theta;
	if (keycode == 125) //down arr 
		view -> theta_x -= d_theta;
	//rotate_mat (eg ctrl + arrow (+ maj for small ones))
	process_and_render(meta);
	return (0);
}

//called when closing window from clicking cross (DESTROY_WIN event)
int	_destroy_hook(void *xp)
{
	mlx_destroy_window(((t_xptr *)xp) -> mlx, ((t_xptr *)xp) -> win);
	exit(0);
	return (0);
}
