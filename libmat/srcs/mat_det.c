/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_det.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 00:15:48 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/15 03:26:18 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

static int	validate_param(t_matrix *mat);
static int	cal_sgn(size_t exp);

//using cofactor expansion(in col 1)
double	mat_det(t_matrix *mat)
{
	size_t		i;
	t_matrix	*submat;
	double		res;

	if (validate_param(mat))
		return (0);
	if (mat->row == 1)
		return (mat->values[0][0]);
	res = 0;
	i = 0;
	while (i < mat->row)
	{
		submat = mat_submat(mat, i, 0);
		res += mat->values[i][0] * cal_sgn(i + 2) * mat_det(submat);
		mat_free(submat);
		++i;
	}
	return (res);
}

static int	cal_sgn(size_t exp)
{
	if (exp % 2 == 0)
		return (1);
	else
		return (-1);
}

static int	validate_param(t_matrix *mat)
{
	if (mat == NULL || mat->values == NULL)
		return (1);
	else if (mat->col != mat->row)
	{
		mat_puterror("mat_det: param is not square matrix\n");
		return (1);
	}
	else
		return (0);
}
