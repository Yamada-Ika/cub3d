/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_rotation_z.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:53:24 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/14 22:53:27 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <math.h>

static void	put_values(double **values, double gamma);

t_matrix	*mat_rotation_z(double gamma)
{
	t_matrix	*res;

	res = mat_identity(4, 4);
	put_values(res->values, gamma);
	return (res);
}

static void	put_values(double **values, double gamma)
{
	values[0][0] = cos(gamma);
	values[0][1] = -sin(gamma);
	values[1][0] = sin(gamma);
	values[1][1] = cos(gamma);
}
