/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 00:55:57 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/25 01:34:44 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static bool	has_read_all_type(int flag)
{
	return (
		flag == (1 << NORTH_PATH_FLAG
			| 1 << SOUTH_PATH_FLAG
			| 1 << WEST_PATH_FLAG
			| 1 << EAST_PATH_FLAG
			| 1 << FLOOR_COLOR_FLAG
			| 1 << CEIL_COLOR_FLAG)
	);
}

static bool	is_type_symbol(char *s)
{
	return (
		is_texture_symbol(s)
		|| is_color_symbol(s)
	);
}

static t_error	parse_type(t_config *config, char *s, int *flag)
{
	if (is_texture_symbol(s))
		return (parse_texture_paths(config, s, flag));
	if (is_color_symbol(s))
		return (parse_colors(config, s, flag));
	return (NO_ERR);
}

static t_error	validate_type(t_config *config)
{
	t_error	err;

	err = validate_texture_path(config);
	if (err != NO_ERR)
		return (err);
	return (NO_ERR);
}

t_error	parse_types(t_config *config)
{
	int		i;
	int		flag;
	t_error	err;

	flag = 0;
	i = -1;
	while (config->cub[++i] != NULL)
	{
		if (ft_strcmp(config->cub[i], "") == 0)
			continue ;
		if (is_type_symbol(config->cub[i]))
			err = parse_type(config, config->cub[i], &flag);
		else
			break ;
		if (err != NO_ERR)
			return (err);
	}
	if (!has_read_all_type(flag))
		return (CUB_ELEMENT_NOT_ENOUGH_ERR);
	config->seek = i - 1;
	return (validate_type(config));
}
