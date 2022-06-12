/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:33:06 by iyamada           #+#    #+#             */
/*   Updated: 2021/10/25 10:55:17 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*c_dst;
	const char	*c_src;

	c_dst = (char *)dst;
	c_src = (const char *)src;
	i = 0;
	while (dst > src && i < len)
	{
		c_dst[len - 1 - i] = c_src[len - 1 - i];
		i++;
	}
	while (dst < src && i < len)
	{
		c_dst[i] = c_src[i];
		i++;
	}
	return (dst);
}
