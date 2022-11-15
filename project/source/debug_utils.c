/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:22:54 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/15 17:23:31 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_imat(t_imat imat)
{
	int i;
	int	j;

	i = 0;
	while (i < imat.m)
	{
		j = 0;
		while (j < imat.n)
		{
			ft_putnbr_fd((imat.imat)[i * imat.n + j], 1);
			ft_putchar_fd(' ', 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	print_fmat(t_fmat fmat)  //to remove after end
{
	int i;
	int	j;

	i = 0;
	while (i < fmat.m)
	{
		j = 0;
		while (j < fmat.n)
		{
			fprintf(stderr, "%f", (fmat.fmat)[i * fmat.n + j]);
			ft_putchar_fd(' ', 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}
