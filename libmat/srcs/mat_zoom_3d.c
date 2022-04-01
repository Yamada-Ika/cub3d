/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_zoom_3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:50:04 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/31 22:51:23 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_matrix	*mat_zoom_3d(double x, double y, double z)
{
	t_matrix	*res;

	res = mat_identity(4, 4);
	res->values[0][0] = x;
	res->values[1][1] = y;
	res->values[2][2] = z;
	return (res);
}
