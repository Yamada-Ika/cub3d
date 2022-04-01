/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_rotation_2d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:38:13 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 00:32:02 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <math.h>
#include <stdio.h>

static void	put_values(double **values, double theta);
static void	do_rotate(t_matrix *a, t_matrix *b);
static void	cpy_res(t_matrix *dst, double src[3][1]);

void	mat_rotation_2d(double theta, t_affine *dst)
{
	t_matrix	*rotation_mat;
	t_matrix	*vec;

	rotation_mat = dst->transform_mat;
	vec = dst->vector;
	put_values(rotation_mat->values, theta);
	do_rotate(rotation_mat, vec);
}

static void	put_values(double **values, double theta)
{
	values[0][0] = cos(theta);
	values[0][1] = -sin(theta);
	values[1][0] = sin(theta);
	values[1][1] = cos(theta);
}

static void	do_rotate(t_matrix *rot_mat, t_matrix *vec)
{
	size_t	i;
	size_t	j;
	size_t	k;
	double	res[3][1];

	i = 0;
	while (i < rot_mat->row)
	{
		j = 0;
		while (j < vec->col)
		{
			res[i][j] = 0;
			k = 0;
			while (k < rot_mat->col)
			{
				res[i][j] += rot_mat->values[i][k] * vec->values[k][j];
				++k;
			}
			++j;
		}
		++i;
	}
	cpy_res(vec, res);
}

static void	cpy_res(t_matrix *dst, double src[3][1])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < dst->row)
	{
		j = 0;
		while (j < dst->col)
		{
			dst->values[i][j] = src[i][j];
			++j;
		}
		++i;
	}
}
