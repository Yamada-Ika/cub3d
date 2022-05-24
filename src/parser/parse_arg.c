/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:52 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/24 18:04:21 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_error	set_sprite_path(t_config *config, char *s)
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

t_error	validate_sprite_paths(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->sp_texs->len)
	{
		if (!has_file_ext(get_texture_path(config, i), ".xpm"))
			return (VALIDATE_SPRITE_TEX_NOT_XPM_ERR);
		if (!can_open(get_texture_path(config, i)))
			return (VALIDATE_SPRITE_TEX_CANT_OPEN_ERR);
		if (is_direcory(get_texture_path(config, i)))
			return (VALIDATE_SPRITE_TEX_IS_DIRECTORY_ERR);
		i++;
	}
	return (NO_ERR);
}

t_error	validate_sprite_id(t_config *config)
{
	int	i;
	int	expect;

	expect = 0;
	i = -1;
	while (++i < config->sp_texs->len)
	{
		// fprintf(stderr, "texture id %d\n", get_texture_id(config, i));
		if (get_texture_id(config, i) < 0)
			return (VALIDATE_INVALID_SPRITE_ID_ERR);
		if (expect == get_texture_id(config, i))
			continue ;
		if (expect + 1 == get_texture_id(config, i))
		{
			expect++;
			continue ;
		}
		return (VALIDATE_INVALID_SPRITE_ID_ERR);
	}
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

bool	should_read_spritepath(t_config *config)
{
	char	**file;
	size_t	i;

	file = config->cub;
	i = config->seek;
	while (file[i] != NULL)
	{
		if (ft_strcmp(file[i], "") == 0)
			break ;
		if (is_sprite_symbol(file[i]))
			return (true);
		i++;
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
	// fprintf(stderr, "-- dump cub --\n");
	// for (int i = 0; config->cub[i] != NULL; i++) {
	// 	fprintf(stderr, "[%s]\n", config->cub[i]);
	// }
	err = parse_tex_paths(config);
	if (err != NO_ERR)
		return (err);
	// fprintf(stderr, "seek [%lld]\n", config->seek);
	// fprintf(stderr, "line [%s]\n", config->cub[config->seek]);
	err = set_color(config);
	if (err != NO_ERR)
		return (err);
	// fprintf(stderr, "seek [%lld]\n", config->seek);
	// fprintf(stderr, "line [%s]\n", config->cub[config->seek]);
	if (should_read_spritepath(config))
	{
		err = parse_sprite_paths(config);
		if (err != NO_ERR)
			return (err);
	}
	// fprintf(stderr, "seek [%lld]\n", config->seek);
	// fprintf(stderr, "line [%s]\n", config->cub[config->seek]);
	err = parse_map(config);
	if (err != NO_ERR)
		return (err);
	return (NO_ERR);
}
