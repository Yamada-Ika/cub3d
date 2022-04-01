/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_distance_2d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:32:02 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/01 21:57:44 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <math.h>

double	mat_distance_2d(t_matrix *matrix)
{
	const double	x_pow_2 = pow(matrix->values[0][0], 2);
	const double	y_pow_2 = pow(matrix->values[1][0], 2);

	return (sqrt(x_pow_2 + y_pow_2));
}
