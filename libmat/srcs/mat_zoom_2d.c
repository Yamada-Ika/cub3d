/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_zoom_2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:50:19 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/01 22:17:55 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

void	mat_zoom_2d(double x, double y, t_affine *dst)
{
	t_matrix	*zoom_mat;
	t_matrix	*vec;

	zoom_mat = dst->transform_mat;
	vec = dst->vector;
	zoom_mat->values[0][0] = x;
	zoom_mat->values[1][1] = y;
	mat_mul(vec, zoom_mat);
}
