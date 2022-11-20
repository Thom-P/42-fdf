/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 20:28:13 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/20 21:17:30 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_fmats_exit(float *fmat, float *init_fmat)
{
	free(fmat);
	free(init_fmat);
	exit(EXIT_FAILURE);
	return ;
}

void	free_word_arr(char **word_arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(word_arr[i]);
		i++;
	}
	free(word_arr);
	return ;
}
