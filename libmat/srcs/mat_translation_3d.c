/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_translation_3d.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:47:44 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/30 17:47:50 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_matrix	*mat_translation_3d(double x, double y, double z)
{
	t_matrix	*res;

	res = mat_identity(4, 4);
	res->values[0][3] = x;
	res->values[1][3] = y;
	res->values[2][3] = z;
	return (res);
}
