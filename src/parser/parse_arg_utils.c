/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:50 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/24 21:14:55 by iyamada          ###   ########.fr       */
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
	i = config->seek;
	while (file[i] != NULL)
	{
		if (ft_strcmp(file[i], "") != 0)
			break ;
		i++;
	}
	config->seek = i;
}

bool	is_texture_symbol(const char *s)
{
	return (
		ft_strncmp(s, "NO ", 3) == 0
		|| ft_strncmp(s, "SO ", 3) == 0
		|| ft_strncmp(s, "WE ", 3) == 0
		|| ft_strncmp(s, "EA ", 3) == 0
	);
}

bool	is_color_symbol(const char *s)
{
	return (
		ft_strncmp(s, "F ", 2) == 0
		|| ft_strncmp(s, "C ", 2) == 0
	);
}

bool	is_sprite_symbol(const char *s)
{
	return (
		ft_strncmp(s, "SP ", 3) == 0
	);
}
