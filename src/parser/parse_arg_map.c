/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:43 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 02:26:37 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

size_t	count_map_heigth(t_config *config)
{
	size_t	i;
	size_t	h;

	h = 0;
	i = config->seek;
	while (config->cub[i + 1] != NULL)
	{
		i++;
		h++;
	}
	return (h);
}

size_t	count_map_width(t_config *config)
{
	return (ft_strlen(config->cub[config->seek]));
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

t_error	new_map(t_config *config)
{
	int		i;
	t_cell	**map;

	skip_newline(config);
	config->height = count_map_heigth(config);
	config->width = count_map_width(config);
	config->map = ft_calloc(config->height, sizeof(t_cell *));
	i = -1;
	while (++i < config->height)
	{
		config->map[i] = ft_calloc(config->width, sizeof(t_cell));
	}
	return (NO_ERR);
}

bool	is_map_symbol(const char c)
{
	return (
		c == 'N'
		|| c == 'S'
		|| c == 'E'
		|| c == 'W'
		|| c == '0'
		|| c == '1'
		|| c == '|'
		|| c == '-'
		|| c == ' '
	);
}

void	set_player_info_in_north(t_config *config, int i, int j)
{
	config->dir_x = -1;
	config->dir_y = 0;
	config->pos_x = i;
	config->pos_y = j;
	config->plane_x = 0;
	config->plane_y = 0.66;
	config->map[i][j].kind = NONE;
}

void	set_player_info_in_south(t_config *config, int i, int j)
{
	config->dir_x = 1;
	config->dir_y = 0;
	config->pos_x = i;
	config->pos_y = j;
	config->plane_x = 0;
	config->plane_y = -0.66;
	config->map[i][j].kind = NONE;
}

void	set_player_info_in_east(t_config *config, int i, int j)
{
	config->dir_x = 0;
	config->dir_y = 1;
	config->pos_x = i;
	config->pos_y = j;
	config->plane_x = 0.66;
	config->plane_y = 0;
	config->map[i][j].kind = NONE;
}

void	set_player_info_in_west(t_config *config, int i, int j)
{
	config->dir_x = 0;
	config->dir_y = -1;
	config->pos_x = i;
	config->pos_y = j;
	config->plane_x = -0.66;
	config->plane_y = 0;
	config->map[i][j].kind = NONE;
}

void	set_map_kind(t_config *config, int i, int j, int kind)
{
	config->map[i][j].kind = kind;
}

void	set_door_info(t_config *config, int i, int j, int kind)
{
	config->map[i][j].kind = DOOR;
	config->map[i][j].door_state = CLOSE;
	config->map[i][j].side = kind;
	config->map[i][j].timer = 0.0;
}

void	set_map_(t_config *config, int i, int j, int idx)
{
	if (config->cub[idx][j] == 'N')
		return (set_player_info_in_north(config, i, j));
	if (config->cub[idx][j] == 'S')
		return (set_player_info_in_south(config, i, j));
	if (config->cub[idx][j] == 'E')
		return (set_player_info_in_east(config, i, j));
	if (config->cub[idx][j] == 'W')
		return (set_player_info_in_west(config, i, j));
	if (config->cub[idx][j] == '0')
		return (set_map_kind(config, i, j, NONE));
	if (config->cub[idx][j] == '1')
		return (set_map_kind(config, i, j, WALL));
	if (config->cub[idx][j] == '|')
		return (set_door_info(config, i, j, LONGITUDINAL));
	if (config->cub[idx][j] == '-')
		return (set_door_info(config, i, j, TRANSVERSE));
}

t_error	set_map(t_config *config)
{
	int		i;
	int		j;
	int		idx;
	int		flag;
	char	*end;
	t_error	err;

	err = new_map(config);
	if (err != NO_ERR)
		return (err);
	idx = config->seek - 1;
	i = -1;
	while (++i < config->height)
	{
		j = -1;
		while (++j < config->width)
		{
			if (is_map_symbol(config->cub[idx][j]))
			{
				set_map_(config, i, j, idx);
				continue ;
			}
			return (UNKNOWN_MAP_SYMBOL);
		}
		idx++;
	}
	return (NO_ERR);
}
