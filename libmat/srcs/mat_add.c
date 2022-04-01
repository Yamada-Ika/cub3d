/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:59:40 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/01 22:46:46 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

static int	validate_params(t_matrix *a, t_matrix *b);

void	mat_add(t_matrix *a, t_matrix *b)
{
	size_t		i;
	size_t		j;

	if (validate_params(a, b))
		return ;
	i = 0;
	while (i < a->row)
	{
		j = 0;
		while (j < a->col)
		{
			a->values[i][j] += b->values[i][j];
			++j;
		}
		++i;
	}
}

static int	validate_params(t_matrix *a, t_matrix *b)
{
	if (a->row != b->row || a->col != b->col)
	{
		mat_puterror(MAT_ADD_ERR);
		return (1);
	}
	return (0);
}
