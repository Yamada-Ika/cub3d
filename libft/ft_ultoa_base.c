/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 02:46:27 by iyamada           #+#    #+#             */
/*   Updated: 2021/11/15 13:07:51 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits_with_radix(unsigned long n, size_t radix)
{
	size_t	digits_count;

	digits_count = 0;
	while (n > 0)
	{
		digits_count++;
		n /= radix;
	}
	return (digits_count);
}

static	char	*ft_chardup(char c)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = c;
	return (str);
}

char	*ft_ultoa_base(unsigned long n, char *base)
{
	size_t	radix;
	size_t	digits_count;
	char	*num;

	if (base == NULL)
		return (NULL);
	if (ft_strcmp(base, "0123456789") == 0)
		return (ft_ultoa(n));
	if (n == 0)
		return (ft_chardup(base[0]));
	radix = ft_strlen(base);
	digits_count = count_digits_with_radix(n, radix);
	num = (char *)ft_calloc(digits_count + 1, sizeof(char));
	if (num == NULL)
		return (NULL);
	while (digits_count-- > 0)
	{
		num[digits_count] = base[n % radix];
		n /= radix;
	}
	return (num);
}
