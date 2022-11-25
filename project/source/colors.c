/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:56:03 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/25 13:42:38 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	_get_z_min_max(float *z_min_max, t_imat *data_in);

int		_read_cmap_file(int cmap[N_CMAP][CMAP_DEPTH]);

//cmap[i] = (int)round((float)RED + ((float)(z_curr - z_min) 
// / (float)(z_max - z_min)) * (float)(WHITE - RED)); 
void	init_colors(t_imat *data_in, t_view *view)
{
	int		*i_color;
	float	z_min_max[2];
	float	z_curr;
	int		nb_pts;

	nb_pts = data_in -> m * data_in -> n;
	i_color = (int *)malloc(sizeof(int) * nb_pts);
	if (i_color == NULL || _read_cmap_file(view -> cmaps) == -1)
	{
		free(i_color);
		free(data_in -> imat);
		perror("In init_colormap");
		exit(EXIT_FAILURE);
	}
	_get_z_min_max(z_min_max, data_in);
	while (nb_pts--)
	{
		z_curr = (float)data_in -> imat[nb_pts];
		i_color[nb_pts] = (int)round((z_curr - z_min_max[0])
				/ (z_min_max[1] - z_min_max[0]) * (CMAP_DEPTH - 1));
	}
	view -> i_color = i_color;
	return ;
}

//load colormaps from file
//fprintf(stderr, "i=%i  cmap[i]=%i\n", i, cmap_vec[i]);
//reverse fill cause reverse z to obtain proper jet map
int	_read_cmap_file(int cmaps[N_CMAP][CMAP_DEPTH])
{
	char	*line;
	int		fd_cmap;
	int		i;

	fd_cmap = open("colormaps.cmap", O_RDONLY);
	if (fd_cmap == -1)
	{
		perror("In read cmap file");
		return (-1);
	}
	i = 0;
	while (i < N_CMAP * CMAP_DEPTH)
	{
		line = get_next_line(fd_cmap);
		if (line == NULL)
		{
			perror("Invalid cmap file");
			return (-1);
		}
		cmaps[i / CMAP_DEPTH][CMAP_DEPTH - 1 - i % CMAP_DEPTH] = ft_atoi(line);
		free(line);
		i++;
	}
	close(fd_cmap);
	return (0);
}

//find min and max values of z in map
void	_get_z_min_max(float *z_min_max, t_imat *data_in)
{
	int		z_min;
	int		z_max;
	int		z_curr;
	int		i;
	int		nb_pts;

	nb_pts = data_in -> m * data_in -> n;
	z_min = INT_MAX;
	z_max = INT_MIN;
	i = 0;
	while (i < nb_pts)
	{
		z_curr = data_in -> imat[i];
		if (z_curr > z_max)
			z_max = z_curr;
		if (z_curr < z_min)
			z_min = z_curr;
		i++;
	}
	z_min_max[0] = (float)z_min;
	z_min_max[1] = (float)z_max;
	return ;
}
