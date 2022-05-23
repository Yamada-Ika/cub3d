/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:50 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 10:20:48 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*skip_spaces(char *s)
{
	while (*s != '\0' && *s == ' ')
		s++;
	return (s);
}

void	skip_newline(t_config *config)
{
	char	**file;
	int		i;

	file = config->cub;
	i = config->seek - 1;
	while (file[++i] != NULL)
	{
		if (ft_strcmp(file[i], "") == 0)
			continue ;
		break ;
	}
	config->seek = i + 1;
}

bool	is_texture_symbol(const char *s)
{
	return (
		ft_strncmp(s, "NO", 2) == 0
		|| ft_strncmp(s, "SO", 2) == 0
		|| ft_strncmp(s, "WE", 2) == 0
		|| ft_strncmp(s, "EA", 2) == 0
	);
}

bool	is_color_symbol(const char *s)
{
	return (
		ft_strncmp(s, "F", 1) == 0
		|| ft_strncmp(s, "C", 1) == 0
	);
}

bool	is_sprite_symbol(const char *s)
{
	return (
		ft_strncmp(s, "SP ", 3) == 0
	);
}
