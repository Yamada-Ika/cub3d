/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:58:33 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/10 18:00:28 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

size_t	next_nonspace(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ' || s[i] == '\t')
			i++;
		else
			return (i);
	}
}

size_t	count_row(char **strs)
{
	size_t	row;

	row = 0;
	while (strs[row] != NULL)
	{
		row++;
	}
	return (row);
}

size_t	count_col(char **strs)
{
	return (ft_strlen(strs[0]));
}

bool	has_ext(const char *path, const char *ext)
{
	char	*dot_at;
	size_t	dot_index;

	if (ft_strlen(path) < ft_strlen(ext))
		return (false);
	dot_at = ft_strrchr(path, '.');
	if (dot_at == NULL)
		return (false);
	dot_index = ++dot_at - path;
	if (ft_strcmp(&path[dot_index], ext) != 0)
		return (false);
	return (true);
}
