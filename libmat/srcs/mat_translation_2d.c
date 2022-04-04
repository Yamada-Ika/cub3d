/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_translation_2d.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 03:00:07 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 03:08:26 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <math.h>

static void	put_translation_mat(double x, double y, t_matrix *mat);
static void	do_translate(t_matrix *trans_mat, t_matrix *vec);
static void	cpy_res(t_matrix *dst, double src[3][1]);

void	mat_translation_2d(double x, double y, t_affine *src)
{
	put_translation_mat(x, y, src->transform_mat);
	do_translate(src->transform_mat, src->vector);
}

static void	put_translation_mat(double x, double y, t_matrix *mat)
{
	mat->values[0][2] = x;
	mat->values[1][2] = y;
}

static void	do_translate(t_matrix *trans_mat, t_matrix *vec)
{
	size_t	i;
	size_t	j;
	size_t	k;
	double	res[3][1];

	i = 0;
	while (i < trans_mat->row)
	{
		j = 0;
		while (j < vec->col)
		{
			res[i][j] = 0;
			k = 0;
			while (k < trans_mat->col)
			{
				res[i][j] += trans_mat->values[i][k] * vec->values[k][j];
				++k;
			}
			++j;
		}
		++i;
	}
	cpy_res(vec, res);
}

static void	cpy_res(t_matrix *dst, double src[3][1])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < dst->row)
	{
		j = 0;
		while (j < dst->col)
		{
			dst->values[i][j] = src[i][j];
			++j;
		}
		++i;
	}
}
