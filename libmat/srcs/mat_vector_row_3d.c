/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_vector_row_3d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:35:48 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/29 20:35:51 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_matrix	*mat_vector_row_3d(double x, double y, double z)
{
	t_matrix	*res;

	res = mat_new(1, 4);
	res->values[0][0] = x;
	res->values[0][1] = y;
	res->values[0][2] = z;
	res->values[0][3] = 1;
	return (res);
}
