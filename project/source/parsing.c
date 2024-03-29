/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:12:57 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/26 20:27:18 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		_parse_file(int fd, t_imat *data_in, t_list **row_list);

static void		_parse_first_line(t_imat *data_in, t_list **row_list, int fd);

static int		_parse_line(char *line, int **row);

static int		*_list2mat(t_list **row_list, int m, int n);

// Get data from .fdf file into int matrix data_in
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
	ft_putstr_fd(f_name, 1);
	ft_putstr_fd(" loading...\n", 1);
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

// Data from each line are stored in a linked list (unknown file dimension)
static int	_parse_file(int fd, t_imat *data_in, t_list **row_list)
{
	int		*row;
	t_list	*node;
	char	*line;
	char	*err_msg;

	_parse_first_line(data_in, row_list, fd);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (0);
		if (_parse_line(line, &row) != data_in -> n)
		{	
			err_msg = "Invalid format file!";
			break ;
		}
		node = ft_lstnew(row);
		if (node == NULL)
			break ;
		ft_lstadd_back(row_list, node);
		(data_in -> m)++;
	}
	perror(err_msg);
	free(row);
	return (-1);
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

// Convert a char line into an int array
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
		free_word_arr(word_arr);
		return (-1);
	}
	n = 0;
	while (word_arr[n] != NULL && *word_arr[n] != '\n')
	{	
		(*row)[n] = ft_atoi(word_arr[n]);
		n++;
	}
	free_word_arr(word_arr);
	return (n);
}

// Convert the linked list into a matrix
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
