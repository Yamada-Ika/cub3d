/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 23:47:47 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/03 00:25:48 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_shift_splitted_word(char const *s, char c)
{
	while (*s != c && *s != '\0')
		s++;
	return ((char *)s);
}

static char	*ft_skip_split_char(char const *s, char c)
{
	while (*s == c && *s != '\0')
		s++;
	return ((char *)s);
}

static char	**ft_split_helper(char const *s, char c, size_t split_num)
{
	const char	*s_ptr;
	char		*split_str;
	char		**split_strs;

	s = ft_skip_split_char(s, c);
	if (*s == '\0')
	{
		split_strs = (char **)ft_xmalloc(sizeof(char *) * (split_num + 1));
		if (split_strs == NULL)
			return (NULL);
		split_strs[split_num] = NULL;
		return (split_strs);
	}
	s_ptr = s;
	s = ft_shift_splitted_word(s, c);
	split_str = ft_substr(s_ptr, 0, s - s_ptr);
	if (split_str == NULL)
		return (NULL);
	split_strs = ft_split_helper(s, c, ++split_num);
	if (split_strs == NULL)
		free(split_str);
	else
		split_strs[split_num - 1] = split_str;
	return (split_strs);
}

char	**ft_split(char const *s, char c)
{
	char	**split_strs;

	if (s == NULL || (*s == '\0' && c == '\0'))
	{
		split_strs = (char **)ft_xmalloc(sizeof(char));
		split_strs[0] = NULL;
		return (split_strs);
	}
	return (ft_split_helper(s, c, 0));
}
