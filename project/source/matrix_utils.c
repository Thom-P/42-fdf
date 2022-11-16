/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:30:14 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/16 15:42:22 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//duplicate float matrix by malloc
t_fmat fmat_dup(t_fmat *fmat_in)
{
	t_fmat	fmat_out;
	int i;

	fmat_out.m = fmat_in -> m;
	fmat_out.n = fmat_in -> n;
	fmat_out.fmat = (float *)malloc(sizeof(float) * fmat_out.m * fmat_out.n);
	i = 0;
	while (i < fmat_out.m * fmat_out.n)
	{
		fmat_out.fmat[i] = fmat_in -> fmat[i];
		i++;
	}
	return (fmat_out);
}
