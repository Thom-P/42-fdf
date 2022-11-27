/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 20:28:13 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/27 18:52:33 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_and_exit(float *fmat, float *init_fmat, int *i_color)
{
	free(fmat);
	free(init_fmat);
	free(i_color);
	exit(EXIT_FAILURE);
	return ;
}

// Free memory allocated by ft_split
void	free_word_arr(char **word_arr)
{
	int	i;

	i = 0;
	while (word_arr[i] != NULL)
	{
		free(word_arr[i]);
		i++;
	}
	free(word_arr);
	return ;
}
