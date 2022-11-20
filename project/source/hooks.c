/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:37:35 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/20 18:57:10 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_down_hook(int keycode, t_meta *meta)
{
	float d_theta;

	//fprintf(stderr, "%i\n", keycode);
	d_theta = meta -> view.d_theta;
	if (keycode == ESCAPE_KEY)
		destroy_hook(&meta -> xp);
	else if (keycode == MAJ_KEY)
		meta -> view.d_theta /= 3;
	else if (keycode == I_KEY) //zoom in
		meta -> view.zoom *= 1.1; 	
	else if (keycode == O_KEY) //zoom out
		meta -> view.zoom /= 1.1;
	else if (keycode == K_KEY) //scale z +
		meta -> view.z_scale *= 1.1;
	else if (keycode == L_KEY) //scale z -
		meta -> view.z_scale /= 1.1;
	else if (keycode == LEFT_ARROW_KEY) 
		meta -> view.theta_z -= d_theta;
	else if (keycode == RIGHT_ARROW_KEY)
		meta -> view.theta_z += d_theta;
	else if (keycode == UP_ARROW_KEY)
		meta -> view.theta_x += d_theta;
	else if (keycode == DOWN_ARROW_KEY)
		meta -> view.theta_x -= d_theta;
	else if (keycode == A_KEY)
		meta -> view.off_x += round(meta -> im.nx / 20);
	else if (keycode == D_KEY)
		meta -> view.off_x -= round(meta -> im.nx / 20);
	else if (keycode == W_KEY)
		meta -> view.off_y += round(meta -> im.ny / 20);
	else if (keycode == S_KEY)
		meta -> view.off_y -= round(meta -> im.ny / 20);
	else 
		return (0);
	process_and_render(meta);
	return (0);
}

int	key_up_hook(int keycode, t_meta *meta)
{
	if (keycode == MAJ_KEY)
		meta -> view.d_theta *= 3;
	return (0);
}

//called when closing window or pressing escape key
int	destroy_hook(void *xp)
{
	mlx_destroy_window(((t_xptr *)xp) -> mlx, ((t_xptr *)xp) -> win);
	// free all mallocs? destroy image? other things
	exit(0);
	return (0);
}
