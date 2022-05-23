/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:46 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/24 01:41:45 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_error	set_texturea_path(t_config *config, char *s, int *flag)
{
	t_error	err;

	err = NO_ERR;
	if (ft_strncmp(s, "NO ", 2) == 0)
		err = set_north(config, s, flag);
	else if (ft_strncmp(s, "SO ", 2) == 0)
		err = set_south(config, s, flag);
	else if (ft_strncmp(s, "WE ", 2) == 0)
		err = set_west(config, s, flag);
	else if (ft_strncmp(s, "EA ", 2) == 0)
		err = set_east(config, s, flag);
	return (err);
}

static bool	has_set_all_textures(const int flag)
{
	return (
		flag == (1 << NORTH_FLAG | 1 << SOUTH_FLAG
			| 1 << WEST_FLAG | 1 << EAST_FLAG)
	);
}

static t_error	set_tex_path(t_config *config)
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
		if (has_set_all_textures(flag))
			break ;
		if (is_texture_symbol(file[i]))
		{
			err = set_texturea_path(config, file[i], &flag);
			continue ;
		}
		return (UNKNOWN_SYMBOL);
	}
	config->seek = i + 1;
	return (NO_ERR);
}

t_error	parse_tex_paths(t_config *config)
{
	t_error	err;

	err = set_tex_path(config);
	if (err != NO_ERR)
		return (err);
	return (validate_texture_path(config));
}
