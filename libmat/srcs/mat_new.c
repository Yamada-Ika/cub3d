/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:40:27 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/30 02:02:39 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <unistd.h>

static void	*mat_calloc(size_t nmemb, size_t size);

t_matrix	*mat_new(size_t row, size_t col)
{
	t_matrix	*res;
	double		**values;
	size_t		i;

	res = (t_matrix *)mat_calloc(1, sizeof(t_matrix));
	values = (double **)mat_calloc(row, sizeof(double *));
	i = 0;
	while (i < row)
	{
		values[i] = mat_calloc(col, sizeof(double));
		++i;
	}
	res->row = row;
	res->col = col;
	res->values = values;
	return (res);
}

static void	mat_bzero(void *dst, size_t size)
{
	size_t			i;
	unsigned char	*uc_dst;

	uc_dst = (unsigned char *)dst;
	i = 0;
	while (i < size)
	{
		uc_dst[i] = 0;
		++i;
	}
}

static void	*mat_calloc(size_t nmemb, size_t size)
{
	void	*res;

	res = malloc(nmemb * size);
	if (res == NULL)
	{
		mat_puterror(MALLOC_ERR);
		exit(1);
	}	
	mat_bzero(res, nmemb * size);
	return (res);
}
