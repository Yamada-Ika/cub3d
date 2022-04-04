/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_mul_scalar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:06:52 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/01 22:06:06 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <stdio.h>

void	mat_mul_scalar(double k, t_matrix *a)
{
	size_t		i;
	size_t		j;

	i = 0;
	while (i < a->row)
	{
		j = 0;
		while (j < a->col)
		{
			a->values[i][j] *= k;
			++j;
		}
		++i;
	}
}
