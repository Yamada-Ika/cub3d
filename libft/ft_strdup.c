/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 23:47:57 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/03 00:25:51 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	s2 = (char *)ft_xmalloc(sizeof(char) * (s1_len + 1));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1, s1_len + 1);
	return (s2);
}
