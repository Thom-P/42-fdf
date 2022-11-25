/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:37:35 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/25 13:57:13 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_shift_view(int key, t_view *view);

static void	_rotate_view(int key, t_view *view);

//fprintf(stderr, "%i\n", key);
int	key_down_hook(int key, t_meta *meta)
{
	if (key == ESCAPE_KEY)
		destroy_hook(meta);
	if (key == SPACE_KEY)
		meta -> view.i_cmap = (meta -> view.i_cmap + 1) % N_CMAP;
	else if (key == MAJ_KEY)
		meta -> view.d_theta /= 3;
	else if (key == I_KEY)
		meta -> view.zoom *= 1.1;
	else if (key == O_KEY)
		meta -> view.zoom /= 1.1;
	else if (key == K_KEY)
		meta -> view.z_scale *= 1.1;
	else if (key == L_KEY)
		meta -> view.z_scale /= 1.1;
	else if (key == LEFT_ARROW_KEY || key == RIGHT_ARROW_KEY
		|| key == UP_ARROW_KEY || key == DOWN_ARROW_KEY)
		_rotate_view(key, &meta -> view);
	else if (key == A_KEY || key == D_KEY || key == W_KEY || key == S_KEY)
		_shift_view(key, &meta -> view);
	else
		return (0);
	process_and_render(meta);
	return (0);
}

static void	_rotate_view(int key, t_view *view)
{	
	if (key == LEFT_ARROW_KEY)
		view -> theta_z -= view -> d_theta;
	else if (key == RIGHT_ARROW_KEY)
		view -> theta_z += view -> d_theta;
	else if (key == UP_ARROW_KEY)
		view -> theta_x += view -> d_theta;
	else if (key == DOWN_ARROW_KEY)
		view -> theta_x -= view -> d_theta;
	return ;
}

static void	_shift_view(int key, t_view *view)
{
	if (key == A_KEY)
		view -> off_x += view -> d_offset;
	else if (key == D_KEY)
		view -> off_x -= view -> d_offset;
	else if (key == W_KEY)
		view -> off_y += view -> d_offset;
	else if (key == S_KEY)
		view -> off_y -= view -> d_offset;
	return ;
}

int	key_up_hook(int keycode, t_meta *meta)
{
	if (keycode == MAJ_KEY)
		meta -> view.d_theta *= 3;
	return (0);
}

//called when closing window or pressing escape key
// nb: if window closed during recomputing could have leaks
int	destroy_hook(t_meta *meta)
{
	free(meta -> init_fmat.fmat);
	free(meta -> view.i_color);
	mlx_destroy_image(meta -> xp.mlx, meta -> im.id);
	mlx_destroy_window(meta -> xp.mlx, meta -> xp.win);
	exit(0);
	return (0);
}
