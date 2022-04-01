/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_l2norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 22:19:05 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/30 17:39:45 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <math.h>

static double	cal_for_row_vector(t_matrix *matrix);
static double	cal_for_col_vector(t_matrix *matrix);

double	mat_l2norm(t_matrix *matrix)
{
	if (matrix->row == 1)
		return (cal_for_row_vector(matrix));
	else if (matrix->col == 1)
		return (cal_for_col_vector(matrix));
	else
	{
		mat_puterror("mat_l2norm: param is not vector\n");
		return (0);
	}
}

static double	cal_for_row_vector(t_matrix *matrix)
{
	size_t	j;
	double	res;

	res = 0;
	j = 0;
	while (j < matrix->col)
	{
		res += pow(matrix->values[0][j], 2);
		++j;
	}
	return (sqrt(res));
}

static double	cal_for_col_vector(t_matrix *matrix)
{
	size_t	i;
	double	res;

	res = 0;
	i = 0;
	while (i < matrix->row)
	{
		res += pow(matrix->values[i][0], 2);
		++i;
	}
	return (sqrt(res));
}
