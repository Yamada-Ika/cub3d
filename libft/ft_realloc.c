/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 01:30:57 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/03 00:25:47 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*res;

	if (ptr == NULL)
		return (ft_xmalloc(size));
	res = ft_xmalloc(size);
	ft_memcpy(res, ptr, size);
	free(ptr);
	return (res);
}

// #include <stdio.h>
// int main(void) {
// 	int *ptr = calloc(10, sizeof(int));
// 	for (int i = 0; i < 10; i++) {
// 		ptr[i] = i;
// 	}
// 	for (int i = 0; i < 10; i++) {
// 		printf("ptr[%d] = %d\n", i, ptr[i]);
// 	}
// 	ptr = ft_realloc(ptr, 20 * sizeof(int));
// 	for (int i = 0; i < 20; i++) {
// 		printf("ptr[%d] = %d\n", i, ptr[i]);
// 	}
// }
