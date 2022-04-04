/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_inv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 01:48:53 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/15 03:25:48 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

static int		validate_param(t_matrix *src);
static t_matrix	*cal_adj_mat(t_matrix *src);
static int		cal_sgn(size_t exp);

//calculate by definition
t_matrix	*mat_inv(t_matrix *src)
{
	t_matrix	*res;
	t_matrix	*adj;

	if (validate_param(src))
		return (NULL);
	adj = cal_adj_mat(src);
	res = mat_mul_scalar(1 / mat_det(src), adj);
	mat_free(adj);
	return (res);
}

static t_matrix	*cal_adj_mat(t_matrix *src)
{
	size_t		i;
	size_t		j;
	t_matrix	*res;
	t_matrix	*tmp;
	t_matrix	*submat;

	res = mat_new(src->row, src->col);
	i = 0;
	while (i < src->row)
	{
		j = 0;
		while (j < src->col)
		{
			submat = mat_submat(src, i, j);
			res->values[i][j] = cal_sgn(i + j + 2) * mat_det(submat);
			mat_free(submat);
			++j;
		}
		++i;
	}
	tmp = res;
	res = mat_transpose(res);
	mat_free(tmp);
	return (res);
}

static int	cal_sgn(size_t exp)
{
	if (exp % 2 == 0)
		return (1);
	else
		return (-1);
}

static int	validate_param(t_matrix *src)
{
	if (src == NULL || src->values == NULL)
		return (1);
	else if (mat_det(src) == 0)
	{
		mat_puterror(MAT_NOT_REGULAR);
		return (1);
	}
	return (0);
}
