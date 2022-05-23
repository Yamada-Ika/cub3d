/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 01:49:32 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/24 02:12:51 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool	is_rectangle(t_config *config)
{
	int	i;

	i = config->seek - 1;
	while (++i < config->height - 1)
	{
		if (ft_strlen(config->cub[i]) != ft_strlen(config->cub[i + 1]))
			return (false);
	}
	return (true);
}

bool	is_player_symbol(cosnt char c)
{
	return (
		c == 'N'
		|| c == 'S'
		|| c == 'E'
		|| c == 'W'
	);
}

bool	has_invalid_char(t_config *config)
{
	int	i;
	int	j;
	int	cnt;

	cnt = 0;
	i = config->seek - 1;
	while (++i < config->height)
	{
		j = -1;
		while (++j < config->width)
		{
			if (is_player_symbol(config->cub[i][j]))
				cnt++;
			if (cnt > 1)
				return (false);
			if (!is_map_symbol(config->cub[i][j]))
				return (false);
		}
	}
	return (true);
}

t_error	validate_map(t_config *config)
{
	if (is_rectangle(config))
		return (VALIDATE_MAP_ISNOT_RECTANGLE_ERR);
	if (has_invalid_char(config))
		return (VALIDATE_MAP_HAS_INVALID_CHAR_ERR);
	return (NO_ERR);
}

t_error	parse_map(t_config *config)
{
	t_error	err;

	err = new_map(config);
	if (err != NO_ERR)
		return (err);
	err = validate_map(config);
	if (err != NO_ERR)
		return (err);
	return (set_map(config));
}
