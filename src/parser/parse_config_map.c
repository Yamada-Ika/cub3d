/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:14:30 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 02:15:03 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	set_map_var(t_cub *cub, t_config *config)
{
	int		x;
	int		y;
	t_point	p;

	cub->map = ft_calloc(1, sizeof(t_map));
	cub->map->map = config->map;
	cub->map->width = config->width;
	cub->map->heigth = config->height;
	cub->map->door_points = vec_new(sizeof(t_point));
	x = -1;
	while (++x < cub->map->heigth)
	{
		y = -1;
		while (++y < cub->map->width)
		{
			if (cub->map->map[x][y].kind == DOOR)
			{
				p.x = x;
				p.y = y;
				vec_push_back(cub->map->door_points, &p);
			}
		}
	}
}

void	set_minimap_var(t_cub *cub)
{
	int	x;
	int	y;

	cub->minimap = ft_calloc(1, sizeof(t_minimap_info));
	cub->minimap->height = 240;
	cub->minimap->width = 240;
	cub->minimap->buf = ft_calloc(240, sizeof(unsigned int *));
	x = -1;
	while (++x < 240)
	{
		cub->minimap->buf[x] = ft_calloc(240, sizeof(unsigned int));
		y = -1;
		while (++y < 240)
			cub->minimap->buf[x][y] = 0xbccddb;
	}
}
