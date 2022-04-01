/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:37:19 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/14 21:39:42 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

void	mat_free(t_matrix *mat)
{
	size_t	i;

	i = 0;
	while (i < mat->row)
	{
		free(mat->values[i]);
		mat->values[i] = NULL;
		++i;
	}
	free(mat->values);
	free(mat);
}
