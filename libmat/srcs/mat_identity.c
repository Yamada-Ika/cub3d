/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_identity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:33:51 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/14 22:36:35 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

static void	put_identity_values(t_matrix *res);

t_matrix	*mat_identity(size_t row, size_t col)
{
	t_matrix	*res;

	res = mat_new(row, col);
	put_identity_values(res);
	return (res);
}

static void	put_identity_values(t_matrix *res)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < res->row)
	{
		j = 0;
		while (j < res->col)
		{
			if (i == j)
				res->values[i][j] = 1;
			++j;
		}
		++i;
	}
}
