/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 01:49:32 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/08 20:56:36 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static bool	is_out_of_range(t_config *config, int row_idx, int col_idx)
{
	return (
		row_idx < 0
		|| config->seek + config->height <= row_idx
		|| col_idx < 0
		|| config->width <= col_idx
	);
}

static int	floodfill(t_config *config, bool **visits, int row_idx, int col_idx)
{
	if (is_out_of_range(config, row_idx, col_idx))
		return (1);
	if (config->cub[row_idx][col_idx] == '1')
		return (0);
	if (visits[row_idx][col_idx])
		return (0);
	visits[row_idx][col_idx] = true;
	if (
		floodfill(config, visits, row_idx, col_idx + 1) != 0
		|| floodfill(config, visits, row_idx - 1, col_idx) != 0
		|| floodfill(config, visits, row_idx, col_idx - 1) != 0
		|| floodfill(config, visits, row_idx + 1, col_idx) != 0
	)
		return (1);
	return (0);
}

static bool	**make_visits(int height, int width)
{
	bool	**res;
	int		i;

	res = ft_calloc(height + 1, sizeof(bool *));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (++i < height)
	{
		res[i] = ft_calloc(width, sizeof(bool));
		if (res[i] == NULL)
		{
			while (--i > 0)
				free(res[i]);
			free(res);
			return (NULL);
		}
	}
	return (res);
}

static bool	is_map_closed(t_config *conf)
{
	bool	**visits;
	bool	ret_value;

	visits = make_visits(conf->seek + conf->height, conf->width);
	if (visits == NULL)
		ret_value = false;
	else
		ret_value = (
				floodfill(conf, visits,
					conf->seek + (int)conf->pos_x, conf->pos_y)
				== 0);
	free_bools(visits);
	return (ret_value);
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
	err = set_map(config);
	if (err != NO_ERR)
		return (err);
	if (!is_map_closed(config))
		return (VALIDATE_MAP_ISNOT_CLOSED_ERR);
	return (NO_ERR);
}
