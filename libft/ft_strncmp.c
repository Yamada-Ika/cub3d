/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 23:47:17 by iyamada           #+#    #+#             */
/*   Updated: 2021/10/25 10:56:57 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char*s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*cu_s1;
	const unsigned char	*cu_s2;

	cu_s1 = (const unsigned char *)s1;
	cu_s2 = (const unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	i = 0;
	while (cu_s1[i] == cu_s2[i] && i < n - 1
		&& !(cu_s1[i] == '\0' && cu_s2[i] == '\0'))
		i++;
	return (cu_s1[i] - cu_s2[i]);
}
