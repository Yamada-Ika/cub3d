/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_path2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:58:28 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/10 17:58:28 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*remove_char(const char *s, const char c)
{
	char	**strs;
	char	*rs;
	size_t	i;

	strs = ft_split(s, c);
	if (strs == NULL)
		return (NULL);
	i = 0;
	rs = ft_strdup("");
	while (strs[i] != NULL)
	{
		rs = append(rs, strs[i]);
		i++;
	}
	return (rs);
}
