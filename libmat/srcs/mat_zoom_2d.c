/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_zoom_2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:50:19 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/31 22:50:43 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_matrix	*mat_zoom_2d(double x, double y)
{
	t_matrix	*res;

	res = mat_identity(3, 3);
	res->values[0][0] = x;
	res->values[1][1] = y;
	return (res);
}
