/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_vector_col_2d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:36:49 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/29 20:37:01 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_matrix	*mat_vector_col_2d(double x, double y)
{
	t_matrix	*res;

	res = mat_new(3, 1);
	res->values[0][0] = x;
	res->values[1][0] = y;
	res->values[2][0] = 1;
	return (res);
}
