/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:12:57 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/14 12:44:49 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_imat	_parse_file(int fd);

static void		_parse_first_line(t_imat *data_in, t_list **row_list, int fd);

static int		_parse_line(char *line, int **row);

static int		*_list2mat(t_list **row_list, int m, int n);

static void		_free_and_exit(t_list **row_list, int *row, char *msg);

t_imat	get_input(char *f_name)
{
	int		fd;
	t_imat	data_in;
	
	fd = open(f_name, O_RDONLY);
	if (fd == -1)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	data_in = _parse_file(fd);
	if (close(fd))
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	return (data_in);
}

static	t_imat	_parse_file(int fd)
{
	t_imat	data_in;
	int		*row;
	t_list	*row_list;
	t_list	*node;
	char	*line;

	_parse_first_line(&data_in, &row_list, fd);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (_parse_line(line, &row) != data_in.n)
			_free_and_exit(&row_list, row, "Invalid format file! \n");
		node = ft_lstnew(row);
		if (node == NULL)
			_free_and_exit(&row_list, row, "Failed malloc during parsing! \n");
		ft_lstadd_back(&row_list, node);
		(data_in.m)++;
	}
	data_in.imat = _list2mat(&row_list, data_in.m, data_in.n);
	return (data_in);
}

static void	_free_and_exit(t_list **row_list, int *row, char *msg)
{
	ft_putstr_fd(msg, 1);
	free(row);
	ft_lstclear(row_list, &free);
	exit(EXIT_FAILURE);
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
		free(row);
		exit(EXIT_FAILURE);
	}	
	data_in -> m = 1;
	return ;
}

static int	*_list2mat(t_list **row_list, int m, int n)
{
	int	*data_mat;
	int	i;
	int	j;
	int	*row;

	i = 0;
	data_mat = (int *)malloc(sizeof(int) * m * n);
	while (*row_list != NULL)
	{	
		row = (*row_list)-> content;
		j = 0;
		while (j < n)
		{
			data_mat[i * n + j] = row[j];
			j++;
		}
		i++;
		*row_list = (*row_list)-> next;
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
