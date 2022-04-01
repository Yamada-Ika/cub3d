/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 23:35:06 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/15 02:19:27 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <stdio.h>

void	mat_print(t_matrix *mat)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < mat->row)
	{
		j = 0;
		while (j < mat->col)
		{
			printf("%f ", mat->values[i][j]);
			++j;
		}
		printf("\n");
		++i;
	}
}
