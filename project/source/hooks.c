/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:37:35 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/19 12:11:55 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_down_hook(int keycode, t_meta *meta)
{
	t_xptr	*xp;
	float d_theta;

	//fprintf(stderr, "%i\n", keycode);
	xp = &meta -> xp; 
	if (keycode == ESCAPE_KEY)
		destroy_hook(xp);
	if (keycode == 257) //MAJ
		meta -> view.d_theta /= 3;
	d_theta = meta -> view.d_theta;
	if (keycode == I_KEY) //zoom in
		meta -> view.zoom *= 1.1; 	
	if (keycode == O_KEY) //zoom out
		meta -> view.zoom /= 1.1;
	if (keycode == K_KEY) //scale z +
		meta -> view.z_scale *= 1.1;
	if (keycode == L_KEY) //scale z -
		meta -> view.z_scale /= 1.1;
	if (keycode == LEFT_ARROW_KEY) 
		meta -> view.theta_z -= d_theta;
	if (keycode == RIGHT_ARROW_KEY)
		meta -> view.theta_z += d_theta;
	if (keycode == UP_ARROW_KEY)
		meta -> view.theta_x += d_theta;
	if (keycode == DOWN_ARROW_KEY)
		meta -> view.theta_x -= d_theta;
	if (keycode == A_KEY)
		meta -> view.off_x += round(meta -> im.nx / 20);
	if (keycode == D_KEY)
		meta -> view.off_x -= round(meta -> im.nx / 20);
	if (keycode == W_KEY)
		meta -> view.off_y += round(meta -> im.ny / 20);
	if (keycode == S_KEY)
		meta -> view.off_y -= round(meta -> im.ny / 20);
	process_and_render(meta);
	return (0);
}

int	key_up_hook(int keycode, t_meta *meta)
{
	if (keycode == 257) //MAJ
		meta -> view.d_theta *= 3;
	return (0);
}

//called when closing window from clicking cross (DESTROY_WIN event)
int	destroy_hook(void *xp)
{
	mlx_destroy_window(((t_xptr *)xp) -> mlx, ((t_xptr *)xp) -> win);
	// free all mallocs? destroy image? other things
	exit(0);
	return (0);
}
