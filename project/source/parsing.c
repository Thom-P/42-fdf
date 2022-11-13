/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:12:57 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/13 15:46:51 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_imat	get_input(char *f_name)
{
	int		fd;
	t_imat	data_in;

	fd = open(f_name, O_RDONLY);
	if (fd == -1)
	{
		perror(NULL);
		exit();
	}
	data_in = _parse_file(fd);
	if (close(fd))
	{
		perror(NULL);
		exit();
	}
	return (data_in);
}

t_imat	_parse_file(int fd)
{
	t_imat	data_in;
	t_imat	row;
	t_list	*row_list;

	line = get_next_line(fd);
	if (line == NULL)
	{	
		ft_putstr_fd("Empty file...\n");
		exit();
	}
	row = _parse_line(line);
	if (row.n < 2)
	{
		ft_putstr_fd("Error: at least two columns required!\n");
		exit();
	}
	row_list = NULL;
	ft_lst_addback(&row_list, ft_lst_new(row.imat));
	data_in.n = row.n;
	data_in.m = 1;
	while (get_next_line(fd))
	{
		row = _parse_line(line);
		if (row.n != data_in.n)
		{	
			ft_putstr_fd("Invalid format file!\n");
			ft_lstclear(&row_list, &free);
			exit();
		}
		ft_lst_addback(&row_list, ft_lst_new(row.imat));
		(data_in.m)++;
	}
	data_in.imat = list2mat(&row_list, data_in.m, data_in.n);
	ft_lstclear(&row_list, &free);
	return (data_in);
}

int	*_list2mat(t_list **row_list, int m, int n)
{
	int *data_mat;
	int i;
	int j;
	int *row;

	i = 0;
	data_mat = (int *)malloc(sizeof(int) * m * n);
	while (*row_list != NULL)
	{	
		row = row_list -> content;
		j = 0;
		while(j < n)	
		{
			data_mat[i * n + j] = row[j];
			j++;
		}
		i++;
	}
	return (data_mat);
}

t_imat _parse_line(char **line)
{
	t_imat	row;
	char	**word_arr;
	int		*row_mat;
	int		n;

	word_arr = ft_split(line);
	n = 0;
	while (word_arr[n] != NULL)
		n++;
	row_mat = (int *)malloc(sizeof(int) * n);
	n = 0;
	while (word_arr[n] != NULL)
	{	
		row_mat[n] = ft_atoi(word_arr[n]);
		free(word_arr[n]);
		n++;
	}
	free(word_arr);
	row.m = 1;
	row.n = n;
	row.imat = row_mat;
	return (row);
}
