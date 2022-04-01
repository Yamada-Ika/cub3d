/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_zoom_2d_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:07:37 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/01 22:08:20 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_matrix	*mat_zoom_2d_new(double x, double y)
{
	t_matrix	*res;

	res = mat_identity(3, 3);
	res->values[0][0] = x;
	res->values[1][1] = y;
	return (res);
}
