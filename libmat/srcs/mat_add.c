/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:59:40 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/14 22:09:41 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

static int	validate_params(t_matrix *a, t_matrix *b);

t_matrix	*mat_add(t_matrix *a, t_matrix *b)
{
	size_t		i;
	size_t		j;
	t_matrix	*res;

	if (validate_params(a, b))
		return (NULL);
	res = mat_new(a->row, a->col);
	i = 0;
	while (i < a->row)
	{
		j = 0;
		while (j < a->col)
		{
			res->values[i][j] = a->values[i][j] + b->values[i][j];
			++j;
		}
		++i;
	}
	return (res);
}

static int	validate_params(t_matrix *a, t_matrix *b)
{
	if (a->row != b->row || a->col != b->col)
	{
		mat_puterror(MAT_ADD_ERR);
		return (1);
	}
	return (0);
}
