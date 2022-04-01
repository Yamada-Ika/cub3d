/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_mul_scalar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:06:52 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/15 02:41:30 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <stdio.h>

t_matrix	*mat_mul_scalar(double k, t_matrix *a)
{
	size_t		i;
	size_t		j;
	t_matrix	*res;

	res = mat_new(a->row, a->col);
	i = 0;
	while (i < a->row)
	{
		j = 0;
		while (j < a->col)
		{
			res->values[i][j] = k * a->values[i][j];
			++j;
		}
		++i;
	}
	return (res);
}
