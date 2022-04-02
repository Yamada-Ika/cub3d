/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:26:11 by iyamada           #+#    #+#             */
/*   Updated: 2022/01/21 18:28:59 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split2(char const *s, char c)
{
	char	**split_strs;

	if (*s == '\0' && c != '\0')
	{
		split_strs = (char **)malloc(2 * sizeof(char));
		split_strs[0] = "\0";
		split_strs[1] = NULL;
		return (split_strs);
	}
	return (ft_split(s, c));
}
