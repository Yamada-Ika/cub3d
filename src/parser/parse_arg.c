/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:52 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 01:57:53 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_error	set_sprite_path(t_config *config, char *s)
{
	t_sprite_path	sp;
	char 			*end;

	sp.group = ft_strtoll(s, &end, 10);
	if (*end != ' ')
		return (INVALID_SPRITE_ID_ERR);
	end = skip_spaces(end);
	sp.path = end;
	vec_push_back(config->sp_texs, &sp);
	return (NO_ERR);
}

void	resize_sprite_num(t_config *config)
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

t_error	set_sprite_paths(t_config *config)
{
	char	**file;
	size_t	i;
	int		flag;
	char	*end;
	t_error	err;

	file = config->cub;
	flag = 0;
	i = config->seek - 1;
	config->sp_texs = vec_new(sizeof(t_sprite_path));
	while (file[++i] != NULL)
	{
		if (ft_strcmp(file[i], "") == 0)
			break ;
		if (is_sprite_symbol(file[i]))
		{
			err = set_sprite_path(config, &file[i][2]);
			if (err != NO_ERR)
				return (err);
		}
	}
	config->seek = i + 1;
	resize_sprite_num(config);
	return (NO_ERR);
}

bool	should_read_spritepath(t_config *config)
{
	char	**file;
	size_t	i;
	int		flag;
	char	*end;

	file = config->cub;
	flag = 0;
	i = config->seek - 1;
	while (file[++i] != NULL)
	{
		if (ft_strcmp(file[i], "") == 0)
			break ;
		if (is_sprite_symbol(file[i]))
			return (true);
	}
	return (false);
}

int	parse_arg(int argc, char **argv, t_config *config)
{
	t_error	err;

	if (argc != 2)
		return (INVALID_ARG_NUM_ERR);
	err = load_cub(config, argv[1]);
	if (err != NO_ERR)
		return (err);
	err = set_tex_path(config);
	if (err != NO_ERR)
		return (err);
	err = set_color(config);
	if (err != NO_ERR)
		return (err);
	if (should_read_spritepath(config))
	{
		err = set_sprite_paths(config);
		if (err != NO_ERR)
			return (err);
	}
	err = set_map(config);
	if (err != NO_ERR)
		return (err);
	return (NO_ERR);
}
