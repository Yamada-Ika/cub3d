/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_zoom_2d_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:07:37 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/03 21:40:29 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_matrix	*mat_zoom_2d_new(double x, double y, t_affine *src)
{
	t_affine	dst;

	dst.vector = mat_dup(src->vector);
	dst.transform_mat = src->transform_mat;
	mat_zoom_2d(x, y, &dst);
	return (dst.vector);
}
