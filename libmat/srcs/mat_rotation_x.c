/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_rotation_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:53:00 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/14 22:53:02 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <math.h>

static void	put_values(double **values, double alpha);

t_matrix	*mat_rotation_x(double alpha)
{
	t_matrix	*res;

	res = mat_identity(4, 4);
	put_values(res->values, alpha);
	return (res);
}

static void	put_values(double **values, double alpha)
{
	values[1][1] = cos(alpha);
	values[1][2] = -sin(alpha);
	values[2][1] = sin(alpha);
	values[2][3] = cos(alpha);
}
