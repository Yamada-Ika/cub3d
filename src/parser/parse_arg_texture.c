/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:46 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 01:57:46 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_error	set_texturea_path(t_config *config, char *s, int *flag)
{
	char	*line;

	if (ft_strncmp(s, "NO", 2) == 0)
	{
		if (*flag >> NORTH_FLAG & 1)
			return (DUPLICATE_NORTH_TEX_ERR);
		config->no_tex_path = ft_strtrim(&s[2], " ");
		*flag |= 1 << NORTH_FLAG;
	}
	else if (ft_strncmp(s, "SO", 2) == 0)
	{
		if (*flag >> SOUTH_FLAG & 1)
			return (DUPLICATE_SOUTH_TEX_ERR);
		config->so_tex_path = ft_strtrim(&s[2], " ");
		*flag |= 1 << SOUTH_FLAG;
	}
	else if (ft_strncmp(s, "WE", 2) == 0)
	{
		if (*flag >> WEST_FLAG & 1)
			return (DUPLICATE_WEST_TEX_ERR);
		config->we_tex_path = ft_strtrim(&s[2], " ");
		*flag |= 1 << WEST_FLAG;
	}
	else if (ft_strncmp(s, "EA", 2) == 0)
	{
		if (*flag >> EAST_FLAG & 1)
			return (DUPLICATE_EAST_TEX_ERR);
		config->ea_tex_path = ft_strtrim(&s[2], " ");
		*flag |= 1 << EAST_FLAG;
	}
	return (NO_ERR);
}

t_error	set_tex_path(t_config *config)
{
	char	**file;
	int		i;
	int		flag;
	t_error	err;

	err = NO_ERR;
	file = config->cub;
	flag = 0;
	i = -1;
	while (file[++i] != NULL)
	{
		if (err != NO_ERR)
			return (err);
		if (flag == (1<<NORTH_FLAG | 1<<SOUTH_FLAG | 1<<WEST_FLAG | 1<<EAST_FLAG))
			break ;
		if (is_texture_symbol(file[i]))
		{
			err = set_texturea_path(config, file[i], &flag);
			continue ;
		}
		if (i > 3)
			return (NOT_ENOUGH_WALL_TEX_ERR);
		return (UNKNOWN_SYMBOL);
	}
	config->seek = i + 1;
	fprintf(stderr, "set_tex_path config->seek %d\n", config->seek);
	return (NO_ERR);
}
