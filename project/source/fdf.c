/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:44:28 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/16 18:25:37 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		_key_hook(int keycode, void *t_p);

int		_destroy_hook(void *xp);

void	_draw_box_image(t_image *im);

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
	
	int		win_nx;
	int		win_ny;
	
	win_nx = 1280; //values for macbook pro full screen
	win_ny = 750;
	float im_win_ratio;

	im_win_ratio = 0.75;

	//t_image	buff; //for later to avoid screen tearing
	t_image	im;

	im.nx = round(im_win_ratio * win_nx);
	im.ny = round(im_win_ratio * win_ny);
	im.pos_x = round(0.5 * (win_nx - im.nx));
	im.pos_y = round(0.5 * (win_ny - im.ny));
	
	// Processing
	
	t_fmat	init_fmat;

	create_init_mat(&data_in, &init_fmat, &im);
	fprintf(stderr, "init float mat created\n");	
	//print_fmat(init_fmat);
	//exit(0);
	
	//rotate_mat (eg ctrl + arrow (+ maj for small ones))
	float theta;
	t_fmat rotZ;
	rotZ.m = 3;
	rotZ.n = 3;
	theta = 45. / 180 * M_PI;
	float rotz_mat[9] = {cosf(theta), -sinf(theta), 0,
						sinf(theta), cosf(theta), 0,
						0, 0, 1};
	rotZ.fmat = rotz_mat;
	//print_fmat(rotZ);
	premult_fmat(&rotZ, &init_fmat);  
	
	//print_fmat(init_fmat);
	//t_fmat	rot_fmat;
	//rot_fmat = init_fmat;
	
	//project mat
	//t_imat	proj_mat;

	//proj_mat = get_proj_mat(&rot_fmat);

	//apply zoom (eg +/- ?)  do both directly in proj op?
	//apply shift (arrows /maj for small)

	// rendering
	
	t_xptr	xp;
	
	create_win(&xp, win_ny, win_nx, "***Fil de Fer***");

	im.id = mlx_new_image(xp.mlx, im.nx, im.ny);
	im.addr = mlx_get_data_addr(im.id, &im.bpp, &im.line_size, &im.endian);

	//fprintf(stderr, "before drawing\n");	
	
	_draw_box_image(&im); //draw a box around the image to see its size while testing

	//test duplicate OK
	/*t_fmat	fmat_bis;
	fmat_bis = fmat_dup(&init_fmat);
	free(init_fmat.fmat);
	init_fmat.fmat = NULL;
	draw_grid_image(&fmat_bis, &im, &data_in); */
	

	draw_grid_image(&init_fmat, &im, &data_in); //data in passed only for dimensions (only mat freed)
	
	//fprintf(stderr, "after drawing\n");	
	mlx_put_image_to_window(xp.mlx, xp.win, im.id, im.pos_x, im.pos_y);
	//fprintf(stderr, "after put image\n");	
	//mlx_pixel_put(xp.mlx, xp.win, p0.x, p0.y, 255);
	//mlx_pixel_put(xp.mlx, xp.win, p1.x, p1.y, 255);

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

void _draw_box_image(t_image *im)
{	
	t_pt2d	top_left;
	t_pt2d	top_right;
	t_pt2d	bottom_left;
	t_pt2d	bottom_right;

	top_left.x = 0;
	top_right.x = im -> nx - 1;
	bottom_left.x = 0;
	bottom_right.x = im -> nx - 1;
	top_left.y = 0;
	top_right.y = 0;
	bottom_left.y = im -> ny - 1;
	bottom_right.y = im -> ny - 1;
	draw_line_image(&top_left, &top_right, im);
	draw_line_image(&top_right, &bottom_right, im);
	draw_line_image(&bottom_right, &bottom_left, im);
	draw_line_image(&bottom_left, &top_left, im);
	return ;
}

/*int _loop_hook(void *xp)
{
	//do what?
	return (0);
}*/
