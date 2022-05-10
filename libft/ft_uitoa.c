/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 00:39:38 by iyamada           #+#    #+#             */
/*   Updated: 2021/11/15 03:51:00 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(unsigned int n)
{
	size_t		digits_count;

	digits_count = 0;
	while (n > 0)
	{
		digits_count++;
		n /= 10;
	}
	return (digits_count);
}

char	*ft_uitoa(unsigned int n)
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
		num[digits_count] = "9876543210123456789"[n % 10 + 9];
		n /= 10;
	}
	return (num);
}
