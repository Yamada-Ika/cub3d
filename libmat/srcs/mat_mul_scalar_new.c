/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_mul_scalar_new.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 21:54:14 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/01 21:54:41 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <stdio.h>

t_matrix	*mat_mul_scalar_new(double k, t_matrix *a)
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
