/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_inner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 22:29:12 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/29 16:52:02 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

static int	validate_params(t_matrix *a, t_matrix *b);

double	mat_inner(t_matrix *a, t_matrix *b)
{
	t_matrix	*a_t;
	t_matrix	*res_mat;
	double		res_value;

	if (validate_params(a, b))
		return (0);
	a_t = mat_transpose(a);
	res_mat = mat_mul(a, b);
	res_value = res_mat->values[0][0];
	mat_free(a_t);
	mat_free(res_mat);
	return (res_value);
}

static int	validate_params(t_matrix *a, t_matrix *b)
{
	if (a == NULL || b == NULL)
	{
		mat_puterror("mat_inner: params are null.\n");
		return (1);
	}
	else if ((a->row != 1 && a->col != 1)
		|| (b->row != 1 && b->col != 1))
	{
		mat_puterror("mat_inner: params are not vector.\n");
		return (1);
	}
	else
		return (0);
}
