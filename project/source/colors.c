/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:56:03 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/25 11:38:40 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	_get_z_min_max(float *z_min_max, t_imat *data_in);

int		_read_cmap_file(int *cmap);

//cmap[i] = (int)round((float)RED + ((float)(z_curr - z_min) 
// / (float)(z_max - z_min)) * (float)(WHITE - RED)); 
int	*init_color_map(t_imat *data_in)
{
	int		*color_vec;
	int		cmap[CMAP_N];
	float	z_min_max[2];
	float	z_curr;
	int		nb_pts;

	nb_pts = data_in -> m * data_in -> n;
	color_vec = (int *)malloc(sizeof(int) * nb_pts);
	if (color_vec == NULL || _read_cmap_file(cmap) == -1)
	{
		free(color_vec);
		free(data_in -> imat);
		perror("In init_colormap");
		exit(EXIT_FAILURE);
	}
	_get_z_min_max(z_min_max, data_in);
	while (nb_pts--)
	{
		z_curr = (float)data_in -> imat[nb_pts];
		color_vec[nb_pts] = cmap[(int)round((z_curr - z_min_max[0])
				/ (z_min_max[1] - z_min_max[0]) * (CMAP_N - 1))];
	}
	return (color_vec);
}

//load colormap from file
//fprintf(stderr, "i=%i  cmap[i]=%i\n", i, cmap_vec[i]);
//reverse fill cause reverse z to obtain proper jet map
int	_read_cmap_file(int *cmap)
{
	char	*line;
	int		fd_cmap;
	int		i;

	fd_cmap = open("jet.cmap", O_RDONLY);
	if (fd_cmap == -1)
	{
		perror("In read cmap file");
		return (-1);
	}
	i = 0;
	while (i < CMAP_N)
	{
		line = get_next_line(fd_cmap);
		if (line == NULL)
		{
			perror("Invalid cmap file");
			return (-1);
		}
		cmap[CMAP_N - 1 - i] = ft_atoi(line);
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
