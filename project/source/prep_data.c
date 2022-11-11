/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:14:27 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/11 18:18:53 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// some test data for visual test

#include "draw_line.h"

int	data[4][6] = {{0, 0, 0, 0, 0, 0}, {0, 1, 2, 2, 1, 0},
	{0, 1, 2, 2, 1, 0}, {0, 0, 0, 0, 0, 0}};
int nx = 6;
int ny = 4;

int xx = 0;
int yy = 0;
int ind_lin = 0;
t_pt2d	t_pt_arr[ny * nx];
int	ind_next[ny * nx][2]; // right and down neighbors

while (yy < ny)
{
	while (xx < nx)
	{
	 	ind_lin = yy * nx + xx;
		t_pt_arr[ind_lin].x = xx;
		t_pt_arr[ind_lin].y = yy;
		if (xx < nx - 1)
			ind_next[ind_lin][0] = ind_lin + 1; 
		else
			ind_next[ind_lin][0] = -1; // for non linked end 
		if (yy < ny - 1)
			ind_next[ind_lin][1] = ind_lin + nx; 
		else
			ind_next[ind_lin][1] = -1; 
		xx++;
	}
	yy++;
}
