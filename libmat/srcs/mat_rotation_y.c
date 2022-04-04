/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_rotation_y.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:53:09 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/14 22:53:13 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <math.h>

static void	put_values(double **values, double beta);

t_matrix	*mat_rotation_y(double beta)
{
	t_matrix	*res;

	res = mat_identity(4, 4);
	put_values(res->values, beta);
	return (res);
}

static void	put_values(double **values, double beta)
{
	values[0][0] = cos(beta);
	values[0][2] = sin(beta);
	values[2][0] = -sin(beta);
	values[2][2] = cos(beta);
}
