/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:37:35 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/18 20:46:01 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_meta *meta)
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
	if (keycode == 34) // i, zoom in
		meta -> view.zoom *= 1.1; 	
	if (keycode == 31) // o, zoom out
		meta -> view.zoom /= 1.1;
	if (keycode == 40) //k, scale z +
		meta -> view.z_scale *= 1.1;
	if (keycode == 37) //l, scale z -
		meta -> view.z_scale /= 1.1;
	//fprintf(stderr, "%i\n", keycode);
	//view = ((t_meta *)meta) -> view; //nb will need rotation from current pos, not init_mat
	view = &meta -> view; //nb will need rotation from current pos, not init_mat
	//if (keycode < 123 || keycode > 126)
	//   return (0);	
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
int	destroy_hook(void *xp)
{
	mlx_destroy_window(((t_xptr *)xp) -> mlx, ((t_xptr *)xp) -> win);
	exit(0);
	return (0);
}
