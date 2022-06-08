/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 00:58:19 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/08 15:08:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_error	set_sprite_path(t_config *config, char *s)
{
	t_sprite_path	sp;
	char			*end;

	sp.group = ft_strtoll(s, &end, 10);
	if (*end != ' ')
		return (INVALID_SPRITE_ID_ERR);
	end = skip_spaces(end);
	sp.path = end;
	vec_push_back(config->sp_texs, &sp);
	return (NO_ERR);
}

static void	resize_sprite_num(t_config *config)
{
	int	old;
	int	i;

	config->sp_num = 0;
	old = -1;
	i = -1;
	while (++i < config->sp_texs->len)
	{
		if (((t_sprite_path *)vec_at(config->sp_texs, i))->group != old)
		{
			config->sp_num++;
			old = ((t_sprite_path *)vec_at(config->sp_texs, i))->group;
		}
	}
}

static t_error	set_sprite_paths(t_config *config)
{
	char	**file;
	size_t	i;
	t_error	err;

	file = config->cub;
	i = config->seek;
	config->sp_texs = vec_new(sizeof(t_sprite_path));
	while (file[i] != NULL)
	{
		if (ft_strcmp(file[i], "") == 0)
			break ;
		if (is_sprite_symbol(file[i]))
		{
			err = set_sprite_path(config, &file[i][2]);
			if (err != NO_ERR)
				return (err);
		}
		i++;
	}
	config->seek = i + 1;
	resize_sprite_num(config);
	return (NO_ERR);
}

t_error	parse_sprite_paths(t_config *config)
{
	t_error	err;

	err = set_sprite_paths(config);
	if (err != NO_ERR)
		return (err);
	err = validate_sprite_paths(config);
	if (err != NO_ERR)
		return (err);
	err = validate_sprite_id(config);
	if (err != NO_ERR)
		return (err);
	return (NO_ERR);
}
