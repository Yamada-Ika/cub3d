/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 00:13:38 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/15 00:14:49 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_matrix	*mat_dup(t_matrix *src)
{
	t_matrix	*res;
	size_t		i;
	size_t		j;

	res = mat_new(src->row, src->col);
	i = 0;
	while (i < src->row)
	{
		j = 0;
		while (j < src->col)
		{
			res->values[i][j] = src->values[i][j];
			++j;
		}
		++i;
	}
	return (res);
}
