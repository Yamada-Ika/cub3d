/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 15:30:43 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/18 18:22:58 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_skip_prefix(const char **str, int *base)
{
	if (*base == 0 || *base == 16)
	{
		if (ft_strlen_s(*str) > 2)
		{
			if ((*str)[0] == '0' && ((*str)[1] == 'x' || (*str)[1] == 'X'))
			{
				*base = 16;
				*str += 2;
				return ;
			}
		}
		if (ft_strlen_s(*str) > 1)
		{
			if ((*str)[0] == '0')
			{
				*base = 8;
				*str += 1;
				return ;
			}
		}
		if (*base == 0)
			*base = 10;
	}
}

static long long	ft_convert_num(char c)
{
	long long	num;

	num = 0;
	if (ft_isalpha(c))
	{
		if ('A' <= c && c <= 'Z')
			c += 32;
		num = c - 'a' + 10;
	}
	else
		num = c - '0';
	return (num);
}

static void	ft_set_sign(const char **str, int *sign)
{
	*sign = 1;
	if (**str == '-' || **str == '+')
	{
		*sign = 44 - **str;
		(*str)++;
	}
}

static bool	ft_is_flow(long long num, long long digit)
{
	return ((LLONG_MIN + digit) / 10 <= num \
		&& num <= (LLONG_MAX - digit) / 10);
}

long long	ft_strtoll(const char *str, char **endptr, int base)
{
	long long	num;
	long long	digit;
	int			sign;

	num = 0;
	while (('\t' <= *str && *str <= '\r') || *str == ' ')
		str++;
	ft_set_sign(&str, &sign);
	ft_skip_prefix(&str, &base);
	while (ft_isalnum(*str))
	{
		digit = ft_convert_num(*str);
		if (digit >= base)
			break ;
		if (ft_is_flow(num, digit))
			num = num * base + digit * sign;
		else if (sign == 1)
			return (LLONG_MAX);
		else
			return (LLONG_MIN);
		str++;
	}
	if (endptr != NULL)
		*endptr = (char *)str;
	return (num);
}
