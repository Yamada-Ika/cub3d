/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_rotation_any.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:57:48 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/14 23:31:42 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <math.h>

static t_matrix	*make_result(double nx, double ny, double nz, double theta);

t_matrix	*mat_rotation_any(t_matrix *vec, double theta)
{
	const double	**values = (const double **)vec->values;
	t_matrix		*res;

	if (vec->col == 1)
		res = make_result(values[0][0], values[1][0], values[2][0], theta);
	else if (vec->row == 1)
		res = make_result(values[0][0], values[0][1], values[0][2], theta);
	else
	{
		mat_puterror("mat_rotation_any: first param should be vector\n");
		res = NULL;
	}
	return (res);
}

static t_matrix	*make_result(double nx, double ny, double nz, double theta)
{
	t_matrix	*res;
	double		**values;

	res = mat_identity(4, 4);
	values = res->values;
	values[0][0] = (nx * nx * (1 - cos(theta))) + cos(theta);
	values[0][1] = (nx * ny * (1 - cos(theta))) - (nz * sin(theta));
	values[0][2] = (nz * nx * (1 - cos(theta))) + (ny * sin(theta));
	values[1][0] = (nx * ny * (1 - cos(theta))) + (nz * sin(theta));
	values[1][1] = (ny * ny * (1 - cos(theta))) + cos(theta);
	values[1][2] = (ny * nz * (1 - cos(theta))) - (nx * sin(theta));
	values[2][0] = (nz * nx * (1 - cos(theta))) - (ny * sin(theta));
	values[2][1] = (ny * nz * (1 - cos(theta))) - (nx * sin(theta));
	values[2][2] = (nz * nz * (1 - cos(theta))) + cos(theta);
	return (res);
}
