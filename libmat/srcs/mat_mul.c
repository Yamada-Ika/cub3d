/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_mul.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:10:19 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/01 23:51:32 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

static int	validate_params(t_matrix *a, t_matrix *b);
static void	cal_mul(t_matrix *a, t_matrix *b);

void	mat_mul(t_matrix *a, t_matrix *b)
{
	if (!validate_params(a, b))
		cal_mul(a, b);
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

static void	cal_mul(t_matrix *a, t_matrix *b)
{
	size_t	i;
	size_t	j;
	size_t	k;
	double	value;

	i = 0;
	while (i < a->row)
	{
		j = 0;
		while (j < b->col)
		{
			value = 0;
			k = 0;
			while (k < a->col)
			{
				value += a->values[i][k] * b->values[k][j];
				++k;
			}
			a->values[i][j] = value;
			++j;
		}
		++i;
	}
}
