/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:37:35 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/26 20:19:54 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_rotate_or_shift_view(int key, t_view *view);

static void	_reset_or_zscale_view(int key, t_view *view, t_imat *data_in);

// Called on every keyboard down press
int	key_down_hook(int key, t_meta *meta)
{
	if (key == ESCAPE_KEY)
		destroy_hook(meta);
	else if (key == R_KEY || key == Z_KEY)
		_reset_or_zscale_view(key, &meta -> view, &meta -> data_in);
	else if (key == SPACE_KEY)
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
		|| key == UP_ARROW_KEY || key == DOWN_ARROW_KEY || key == A_KEY
		|| key == D_KEY || key == W_KEY || key == S_KEY)
		_rotate_or_shift_view(key, &meta -> view);
	else
		return (0);
	process_and_render(meta);
	return (0);
}

// Called on every key release, used only to increase rotation rate
int	key_up_hook(int keycode, t_meta *meta)
{
	if (keycode == MAJ_KEY)
		meta -> view.d_theta *= 3;
	return (0);
}

static void	_rotate_or_shift_view(int key, t_view *view)
{	
	if (key == LEFT_ARROW_KEY)
		view -> theta_z -= view -> d_theta;
	else if (key == RIGHT_ARROW_KEY)
		view -> theta_z += view -> d_theta;
	else if (key == UP_ARROW_KEY)
		view -> theta_x += view -> d_theta;
	else if (key == DOWN_ARROW_KEY)
		view -> theta_x -= view -> d_theta;
	else if (key == A_KEY)
		view -> off_x += view -> d_offset;
	else if (key == D_KEY)
		view -> off_x -= view -> d_offset;
	else if (key == W_KEY)
		view -> off_y += view -> d_offset;
	else if (key == S_KEY)
		view -> off_y -= view -> d_offset;
	return ;
}

static void	_reset_or_zscale_view(int key, t_view *view, t_imat *data_in)
{
	float	delta_z;
	float	delta_x;

	if (key == R_KEY)
	{
		view -> theta_z = 45. / 180. * M_PI;
		view -> theta_x = -(90. - 35.2644) / 180. * M_PI;
		view -> zoom = 1;
		view -> z_scale = 1;
		view -> off_x = 0;
		view -> off_y = 0;
	}
	else if (key == Z_KEY)
	{
		delta_z = (float)fabsf(view -> z_min_max[1] - view -> z_min_max[0]);
		delta_x = (float) data_in -> n - 1;
		view -> z_scale = 10. / 100 * delta_x / delta_z;
	}
	return ;
}

// Called when closing window or pressing escape key
int	destroy_hook(t_meta *meta)
{
	free(meta -> init_fmat.fmat);
	free(meta -> curr_fmat.fmat);
	free(meta -> view.i_color);
	mlx_destroy_image(meta -> xp.mlx, meta -> im.id);
	mlx_destroy_window(meta -> xp.mlx, meta -> xp.win);
	exit(0);
	return (0);
}
