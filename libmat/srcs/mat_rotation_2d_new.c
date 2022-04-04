/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_rotation_2d_new.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:38:13 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 02:33:13 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <math.h>

t_matrix	*mat_rotation_2d_new(double theta, t_affine *src)
{
	t_affine	dst;

	dst.transform_mat = src->transform_mat;
	dst.vector = mat_dup(src->vector);
	mat_rotation_2d(theta, &dst);
	return (dst.vector);
}
