/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_transpose.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 00:09:27 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/15 00:11:59 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_matrix	*mat_transpose(t_matrix *mat)
{
	t_matrix	*res;
	size_t		i;
	size_t		j;

	res = mat_new(mat->col, mat->row);
	i = 0;
	while (i < mat->row)
	{
		j = 0;
		while (j < mat->col)
		{
			res->values[i][j] = mat->values[j][i];
			++j;
		}
		++i;
	}
	return (res);
}
