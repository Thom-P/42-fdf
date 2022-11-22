/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:12:57 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/22 10:55:55 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		_parse_file(int fd, t_imat *data_in, t_list **row_list);

static void		_parse_first_line(t_imat *data_in, t_list **row_list, int fd);

static int		_parse_line(char *line, int **row);

static int		*_list2mat(t_list **row_list, int m, int n);

t_imat	get_input(char *f_name)
{
	int		fd;
	t_imat	data_in;
	t_list	*row_list;

	fd = open(f_name, O_RDONLY);
	if (fd == -1)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	if (_parse_file(fd, &data_in, &row_list) == -1)
	{
		ft_lstclear(&row_list, &free);
		exit(EXIT_FAILURE);
	}
	data_in.imat = _list2mat(&row_list, data_in.m, data_in.n);
	if (close(fd) || data_in.imat == NULL)
	{
		perror(NULL);
		free(data_in.imat);
		exit(EXIT_FAILURE);
	}
	return (data_in);
}

static int	_parse_file(int fd, t_imat *data_in, t_list **row_list)
//nb: on macbook, need err_msg to be initialized to NULL (not automatic!!)
{
	int		*row;
	t_list	*node;
	char	*line;
	char	*err_msg;

	err_msg = NULL;
	_parse_first_line(data_in, row_list, fd);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (_parse_line(line, &row) != data_in -> n)
			err_msg = "Invalid format file!";
		node = ft_lstnew(row);
		if (node == NULL || err_msg != NULL)
		{	
			perror(err_msg);
			free(row);
			return (-1);
		}
		ft_lstadd_back(row_list, node);
		(data_in -> m)++;
	}
	return (0);
}

static void	_parse_first_line(t_imat *data_in, t_list **row_list, int fd)
{	
	char	*line;
	int		*row;					

	line = get_next_line(fd);
	if (line == NULL)
	{	
		ft_putstr_fd("Empty file...\n", 1);
		exit(EXIT_FAILURE);
	}
	data_in -> n = _parse_line(line, &row);
	if (data_in -> n < 2)
	{
		ft_putstr_fd("Error: at least two columns required!\n", 1);
		free(row);
		exit(EXIT_FAILURE);
	}
	*row_list = ft_lstnew(row);
	if (*row_list == NULL)
	{
		perror(NULL);
		free(row);
		exit(EXIT_FAILURE);
	}	
	data_in -> m = 1;
	return ;
}

static int	*_list2mat(t_list **row_list, int m, int n)
{
	int		*data_mat;
	int		i;
	int		j;
	int		*row;
	t_list	*node;

	node = *row_list;
	i = 0;
	data_mat = (int *)malloc(sizeof(int) * m * n);
	while (data_mat && node != NULL)
	{	
		row = node -> content;
		j = 0;
		while (j < n)
		{
			data_mat[i * n + j] = row[j];
			j++;
		}
		i++;
		node = node -> next;
	}
	ft_lstclear(row_list, &free);
	return (data_mat);
}

static int	_parse_line(char *line, int **row)
{
	char	**word_arr;
	int		n;

	word_arr = ft_split(line, ' ');
	free(line);
	if (word_arr == NULL)
		return (-1);
	n = 0;
	while (word_arr[n] != NULL)
		n++;
	*row = (int *)malloc(sizeof(int) * n);
	if (*row == NULL)
	{	
		free_word_arr(word_arr, n);
		return (-1);
	}
	n = 0;
	while (word_arr[n] != NULL && *word_arr[n] != '\n')
	{	
		(*row)[n] = ft_atoi(word_arr[n]);
		free(word_arr[n]);
		n++;
	}
	free(word_arr);
	return (n);
}
