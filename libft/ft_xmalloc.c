/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:20:40 by kkaneko           #+#    #+#             */
/*   Updated: 2022/06/03 00:22:10 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	*ft_xmalloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (res == NULL)
	{
		printf("Malloc failed.\n");
		exit(1);
	}
	return (res);
}
