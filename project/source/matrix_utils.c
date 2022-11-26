/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:30:14 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/26 20:42:06 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Duplicate float matrix using malloc
t_fmat	fmat_dup(t_fmat *fmat_in)
{
	t_fmat	fmat_out;
	int		i;

	fmat_out.m = fmat_in -> m;
	fmat_out.n = fmat_in -> n;
	fmat_out.fmat = (float *)malloc(sizeof(float) * fmat_out.m * fmat_out.n);
	if (fmat_out.fmat == NULL)
	{
		perror("In fmat_dup");
		free(fmat_in -> fmat);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < fmat_out.m * fmat_out.n)
	{
		fmat_out.fmat[i] = fmat_in -> fmat[i];
		i++;
	}
	return (fmat_out);
}

/* Get matrix C(m, n) by multiplication of matrix A(m, m) by matrix B(m, n)
C = A * B (naive implementation) */
void	mult_fmat(t_fmat *C, t_fmat *A, t_fmat *B)
{
	int	m;
	int	n;
	int	i;
	int	j;
	int	k;

	m = C -> m;
	n = C -> n;
	i = 0;
	while (i < m)
	{
		j = 0;
		while (j < n)
		{
			k = -1;
			C -> fmat[i * n + j] = 0;
			while (++k < m)
				C -> fmat[i * n + j]
					+= A -> fmat[i * m + k] * B -> fmat[k * n + j];
			j++;
		}
		i++;
	}
	return ;
}
