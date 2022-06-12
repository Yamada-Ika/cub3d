/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_common.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 07:26:10 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/12 19:27:36 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static bool	valid_shape_and_size(t_config *config)
{
	int		i;
	int		offset;
	size_t	w;
	size_t	h;

	i = config->seek;
	offset = i;
	h = 0;
	while (i < offset + config->height - 1)
	{
		w = ft_strlen(config->cub[i]);
		if (w != ft_strlen(config->cub[i + 1]))
			return (false);
		if (h > MAP_HEIGHT || w > MAP_WIDTH)
			return (false);
		i++;
		h++;
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
	if (!valid_shape_and_size(config))
		return (VALIDATE_MAP_ISNOT_RECTANGLE_ERR);
	if (!has_valid_char(config))
		return (VALIDATE_MAP_HAS_INVALID_CHAR_ERR);
	return (NO_ERR);
}
