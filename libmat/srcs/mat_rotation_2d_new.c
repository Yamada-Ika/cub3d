/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_rotation_2d_new.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:38:13 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/01 20:41:23 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <math.h>

static void	put_values(double **values, double theta);

t_matrix	*mat_rotation_2d_new(double theta)
{
	t_matrix	*res;

	res = mat_identity(3, 3);
	put_values(res->values, theta);
	return (res);
}

static void	put_values(double **values, double theta)
{
	values[0][0] = cos(theta);
	values[0][1] = -sin(theta);
	values[1][0] = sin(theta);
	values[1][1] = cos(theta);
}
