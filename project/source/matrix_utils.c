/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:30:14 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/26 17:29:36 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//static float	_dot_pro(float *a, float *b, int dim);

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


/* In place (pre)multiplication of matrix A (3, n) by matrix B(3, 3)
A = BxA */
/*void	premult_fmat(t_fmat *B, t_fmat *A)
{
	int		i;
	int		j;
	float	tmp_col[3];

	if (B -> m != 3 || B -> n != 3 || A -> m != 3)
	{
		perror("Invalid matrix size in premult_fmat");
		free(A -> fmat);
		exit(EXIT_FAILURE);
	}
	j = 0;
	while (j < A -> n)
	{
		tmp_col[0] = A -> fmat[j];
		tmp_col[1] = A -> fmat[j + A -> n];
		tmp_col[2] = A -> fmat[j + 2 * A -> n];
		i = 0;
		while (i < 3)
		{
			A -> fmat[j + i * A -> n] = _dot_pro(B -> fmat + i * 3, tmp_col, 3);
			i++;
		}
		j++;
	}
	return ;
}*/

/* Get matrix C(m, n) by multiplication of matrix A(m, m) by matrix B(m, n)
C = A*B */
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
			k = 0;
			C -> fmat[i * n + j] = 0;
			while (k < m)
			{
				C -> fmat[i * n + j] += A -> fmat[i * m + k] * B -> fmat[k * n + j];
				k++;
			}
			j++;
		}
		i++;
	}
	return ;
}

// Dot product
/*static float	_dot_pro(float *a, float *b, int dim)
{
	int		i;
	float	res;

	res = 0;
	i = 0;
	while (i < dim)
	{
		res += a[i] * b[i];
		i++;
	}
	return (res);
}*/
