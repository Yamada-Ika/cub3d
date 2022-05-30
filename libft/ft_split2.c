/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:26:11 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/30 19:08:43 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_size_except_null(char const *s, char c)
{
	size_t	res;

	res = 0;
	while (*s != '\0')
	{
		if (*s == c)
			res++;
		s++;
	}
	return (res + 1);
}

static long long	find(const char *s, const char c)
{
	long long	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_split2(char const *s, char c)
{
	char		**strs;
	size_t		size;
	size_t		i;
	long long	idx;

	size = count_size_except_null(s, c);
	i = 0;
	strs = ft_xmalloc((size + 1) * sizeof(char *));
	strs[size] = NULL;
	while (i < size)
	{
		idx = find(s, c);
		if (idx == -1)
		{
			strs[i] = ft_substr(s, 0, ft_strlen(s));
			break ;
		}
		strs[i] = ft_substr(s, 0, (size_t)idx);
		i++;
		s = s + (size_t)idx + 1;
	}
	return (strs);
}
