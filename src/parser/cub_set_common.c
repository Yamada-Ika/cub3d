/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:25:45 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 19:33:56 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	set_mlx_var(t_cub *cub)
{
	cub->window = init_window(WIN_W, WIN_H, "cub3d");
}

void	set_player_var(t_cub *cub, t_config *config)
{
	cub->player = ft_calloc(1, sizeof(t_player));
	cub->player->pos_x = config->pos_x;
	cub->player->pos_y = config->pos_y;
	cub->player->dir_x = config->dir_x;
	cub->player->dir_y = config->dir_y;
	cub->player->plane_x = config->plane_x;
	cub->player->plane_y = config->plane_y;
}

void	set_color_var(t_cub *cub, t_config *config)
{
	cub->map->floor = config->floor_color;
	cub->map->ceil = config->ceil_color;
}

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

void	set_camera_var(t_cub *cub)
{
	cub->camera = ft_calloc(1, sizeof(t_camera));
}
