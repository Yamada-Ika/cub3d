/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 03:50:48 by iyamada           #+#    #+#             */
/*   Updated: 2021/11/15 03:52:26 by iyamada          ###   ########.fr       */
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

char	*ft_uitoa_base(unsigned int n, char *base)
{
	size_t	radix;
	size_t	digits_count;
	char	*num;

	if (base == NULL)
		return (NULL);
	if (ft_strcmp(base, "0123456789") == 0)
		return (ft_ultoa(n));
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
