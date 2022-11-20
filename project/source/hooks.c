/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:37:35 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/20 19:43:41 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_shift_view(int key, t_view *view);

static void	_rotate_view(int key, t_view *view);

//fprintf(stderr, "%i\n", keycode);
int	key_down_hook(int key, t_meta *meta)
{
	if (key == ESCAPE_KEY)
		destroy_hook(&meta -> xp);
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
// free all mallocs? destroy image? other things
int	destroy_hook(void *xp)
{
	mlx_destroy_window(((t_xptr *)xp)-> mlx, ((t_xptr *)xp)-> win);
	exit(0);
	return (0);
}
