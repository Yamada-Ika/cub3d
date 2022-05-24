/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 07:26:10 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/24 23:54:00 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static bool	is_rectangle(t_config *config)
{
	int	i;
	int	offset;

	i = config->seek;
	offset = i;
	while (i < offset + config->height - 1)
	{
		if (ft_strlen(config->cub[i]) != ft_strlen(config->cub[i + 1]))
			return (false);
		i++;
	}
	return (true);
}

static bool	is_player_symbol(const char c)
{
	return (
		c == 'N'
		|| c == 'S'
		|| c == 'E'
		|| c == 'W'
	);
}

static bool	has_valid_char(t_config *config)
{
	int	i;
	int	j;
	int	player_cnt;
	int	offset;

	player_cnt = 0;
	i = config->seek;
	offset = i;
	while (i < offset + config->height)
	{
		j = 0;
		while (j < config->width)
		{
			if (is_player_symbol(config->cub[i][j]))
				player_cnt++;
			if (player_cnt > 1)
				return (false);
			if (!is_map_symbol(config->cub[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (player_cnt == 1);
}

t_error	validate_map(t_config *config)
{
	if (!is_rectangle(config))
		return (VALIDATE_MAP_ISNOT_RECTANGLE_ERR);
	if (!has_valid_char(config))
		return (VALIDATE_MAP_HAS_INVALID_CHAR_ERR);
	return (NO_ERR);
}
