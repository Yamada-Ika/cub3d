/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 02:57:18 by iyamada           #+#    #+#             */
/*   Updated: 2021/11/15 03:16:45 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(unsigned long n)
{
	size_t	digits_count;

	digits_count = 0;
	while (n > 0)
	{
		digits_count++;
		n /= 10;
	}
	return (digits_count);
}

char	*ft_ultoa(unsigned long n)
{
	size_t	digits_count;
	char	*num;

	if (n == 0)
		return (ft_strdup("0"));
	digits_count = count_digits(n);
	num = (char *)ft_calloc(digits_count + 1, sizeof(char));
	if (num == NULL)
		return (NULL);
	while (digits_count-- > 0)
	{
		num[digits_count] = "0123456789"[n % 10];
		n /= 10;
	}
	return (num);
}
