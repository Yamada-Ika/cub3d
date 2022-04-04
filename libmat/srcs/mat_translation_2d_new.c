/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_translation_2d_new.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 03:06:08 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 03:07:20 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_matrix	*mat_translation_2d_new(double x, double y, t_affine *src)
{
	t_affine	dst;

	dst.transform_mat = src->transform_mat;
	dst.vector = mat_dup(src->vector);
	mat_translation_2d(x, y, &dst);
	return (dst.vector);
}
