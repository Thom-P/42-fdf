/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 20:28:13 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/20 20:56:21 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
