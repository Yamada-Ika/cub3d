/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:57:36 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/10 17:57:36 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	parse_file_path(const char *path)
{
	if (!has_ext(path, "cub"))
		return (INVALID_CUB_FILE);
	return (NO_ERR);
}

char	*append(char *dst, char *src)
{
	char	*tmp_1;
	char	*tmp_2;
	char	*new;

	tmp_1 = dst;
	tmp_2 = src;
	new = ft_strjoin(dst, src);
	free(tmp_1);
	free(tmp_2);
	return (new);
}

void	set_map(t_config *this, char *line)
{
	this->map = ft_split(line, '\n');
}
