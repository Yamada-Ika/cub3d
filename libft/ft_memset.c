/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 23:47:33 by iyamada           #+#    #+#             */
/*   Updated: 2021/10/25 10:55:25 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*uc_b;

	i = 0;
	uc_b = (unsigned char *)b;
	while (i < len)
	{
		uc_b[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
