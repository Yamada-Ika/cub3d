/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 12:23:10 by iyamada           #+#    #+#             */
/*   Updated: 2021/10/25 10:57:21 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*head;
	char const	*tail;

	if (s1 == NULL || set == NULL)
		return (NULL);
	head = s1;
	while (*head != '\0' && ft_strchr(set, (int)*head))
		head++;
	if (*head == '\0')
		return (ft_strdup(""));
	tail = s1 + ft_strlen(s1) - 1;
	while (ft_strchr(set, (int)*tail))
		tail--;
	return (ft_substr(head, 0, tail - head + 1));
}
