/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:12:30 by iyamada           #+#    #+#             */
/*   Updated: 2021/10/31 00:12:25 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	size_t	s_len;
	size_t	i;
	char	tmp;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	while (i < s_len / 2)
	{
		tmp = s[i];
		s[i] = s[s_len - (i + 1)];
		s[s_len - (i + 1)] = tmp;
		i++;
	}
	return (s);
}
