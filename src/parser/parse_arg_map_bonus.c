/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_map_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:43 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 16:15:21 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

void	set_map_kind(t_config *config, int i, int j, int kind)
{
	config->map[i][j].kind = kind;
}

void	set_door_info(t_config *config, int i, int j, int side)
{
	config->map[i][j].kind = DOOR;
	config->map[i][j].door_state = CLOSE;
	config->map[i][j].side = side;
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

	idx = config->seek;
	i = 0;
	while (i < config->height)
	{
		j = 0;
		while (j < config->width)
		{
			if (is_map_symbol(config->cub[idx][j]))
				set_map_(config, i, j, idx);
			else
				return (UNKNOWN_MAP_SYMBOL);
			j++;
		}
		idx++;
		i++;
	}
	return (NO_ERR);
}
