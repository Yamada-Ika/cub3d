/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_minimap_buf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:17:15 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 16:17:23 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static bool	is_barricade(t_cub *cub, int x, int y)
{
	t_cell	**map;

	map = cub->map->map;
	return (
		map[x][y].kind == NONE
			|| (map[x][y].kind == DOOR && map[x][y].door_state == OPEN)
	);
}

static bool	is_out_of_range(t_cub *cub, int x, int y)
{
	t_map	*map_info;

	map_info = cub->map;
	return (
		x < 0 || x >= map_info->heigth || y < 0 || y >= map_info->width
	);
}

void	fill_minimap_buf(t_cub *cub)
{
	int				i;
	int				j;
	int				trans_i;
	int				trans_j;
	unsigned int	color;

	i = -1;
	while (++i < MINIMAP_SIZE)
	{
		j = -1;
		while (++j < MINIMAP_SIZE)
		{
			trans_i = i / 20 + cub->player->pos_x - 6;
			trans_j = j / 20 + cub->player->pos_y - 6;
			if (is_out_of_range(cub, trans_i, trans_j))
				continue ;
			if (is_barricade(cub, trans_i, trans_j))
				color = 0x003f8e;
			else
				color = 0xbccddb;
			cub->minimap->buf[i][j] = color;
		}
	}
}
