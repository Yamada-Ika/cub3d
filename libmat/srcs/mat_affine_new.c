/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_affine_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 00:13:52 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 00:31:59 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include <stdio.h>

static void	*ft_calloc(size_t nmemb, size_t size);

t_affine	*mat_affine_new(size_t dimension)
{
	t_affine	*res;

	res = (t_affine *)ft_calloc(1, sizeof(t_affine));
	res->transform_mat = mat_identity(dimension + 1, dimension + 1);
	return (res);
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*uc_s;
	size_t			i;

	uc_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		uc_s[i] = 0;
		++i;
	}
}

static void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	res = malloc(size * nmemb);
	if (res == NULL)
	{
		printf(MALLOC_ERR);
		exit(1);
	}
	ft_bzero(res, size * nmemb);
	return (res);
}
