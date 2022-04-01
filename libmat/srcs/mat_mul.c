/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_mul.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:10:19 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/30 18:58:58 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

static int	validate_params(t_matrix *a, t_matrix *b);
static void	cal_mul(t_matrix *res, t_matrix *a, t_matrix *b);

t_matrix	*mat_mul(t_matrix *a, t_matrix *b)
{
	t_matrix	*res;

	if (validate_params(a, b))
		return (NULL);
	res = mat_new(a->row, b->col);
	cal_mul(res, a, b);
	return (res);
}

static int	validate_params(t_matrix *a, t_matrix *b)
{
	if (a->col != b->row)
	{
		mat_puterror(MAT_MUL_ERR);
		return (1);
	}
	return (0);
}

static void	cal_mul(t_matrix *res, t_matrix *a, t_matrix *b)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (i < a->row)
	{
		j = 0;
		while (j < b->col)
		{
			k = 0;
			while (k < a->col)
			{
				res->values[i][j] += a->values[i][k] * b->values[k][j];
				++k;
			}
			++j;
		}
		++i;
	}
}
