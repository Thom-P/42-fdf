/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:12:57 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/14 10:28:01 by tplanes          ###   ########.fr       */
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
	data_in = _parse_file(fd); //protect?
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
	int		*row;
	t_list	*row_list;

	line = get_next_line(fd);
	if (line == NULL)
	{	
		ft_putstr_fd("Empty file...\n");
		exit();
	}
	nn = _parse_line(line, &row);
	free(line);
	if (row.n < 2) //possibly remove at the end
	{
		ft_putstr_fd("Error: at least two columns required!\n");
		
		exit();
	}
	data_in.n = row.n;
	row_list = ft_lst_new(row.imat); //shld protect lst_new...
	//ft_lst_addback(&row_list, ft_lst_new(row.imat)); //shld protect lst_new...
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

int	_parse_line(char **line, int **row)
{
	char	**word_arr;
	int		*row_mat;
	int		n;

	word_arr = ft_split(line);
	free(line);
	if (word_arr == NULL)
		return (-1);
	n = 0;
	while (word_arr[n] != NULL)
		n++;
	*row = (int *)malloc(sizeof(int) * n);
	if (*row == NULL)
		return (-1);
	n = 0;
	while (word_arr[n] != NULL)
	{	
		(*row)[n] = ft_atoi(word_arr[n]);
		free(word_arr[n]);
		n++;
	}
	free(word_arr);
	return (n);
}
