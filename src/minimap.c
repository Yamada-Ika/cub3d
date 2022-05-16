/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:34:48 by kkaneko           #+#    #+#             */
/*   Updated: 2022/05/17 03:01:51 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical(t_cub *cub, int x, int from, int to, unsigned int color)
{
	int	i;

	i = from;
	while (i < to)
	{
		put_pixel(cub, x, i, color);
		i++;
	}
}

void	fill_buf(t_cub *cub)
{
	t_map	*map_info = cub->map;
	int		pos_x = cub->player->pos_x;
	int		pos_y = cub->player->pos_y;

	for (int i = 0; i < 240; i++) {
		for (int j = 0; j < 240; j++) {
			int trans_i = i / 20 + pos_x - 6;
			int trans_j = j / 20 + pos_y - 6;
			unsigned int color;

			if (trans_i < 0 || trans_i >= map_info->heigth
				|| trans_j < 0 || trans_j >= map_info->width)
				continue;
			if (map_info->map[trans_i][trans_j].kind == WALL)
				color = 0xbccddb; // wall
			else if (map_info->map[trans_i][trans_j].kind == DOOR
				&& map_info->map[trans_i][trans_j].door_state == CLOSE)
				color = 0x000000; // door
			else
				color = 0x003f8e;
			cub->minimap->buf[i][j] = color;
		}
	}
}

unsigned int	get_minimap_color(t_cub *cub, int x, int y)
{
	return cub->minimap->buf[x][y];
}

void	draw_minimap(t_cub *cub)
{
	int	r = 120;
	int x0 = 120;
	int y0 = 120;

	fill_buf(cub);
	for (int x = 0; x < r; x++) {
		int y = sqrt(r*r - x*x);

		int from = -y + y0;
		int to = y + y0;
		while (from < to)
		{
			put_pixel(cub, -x + x0, from, get_minimap_color(cub, from, -x + x0));
			from++;
		}
		from = -y + y0;
		to = y + y0;
		while (from < to)
		{
			put_pixel(cub, x + x0, from, get_minimap_color(cub, from, x + x0));
			from++;
		}
	}

	int r_player = 10;
	for (int x = 0; x < r_player; x++) {
		int y = sqrt(r_player*r_player - x*x);

		int from = -y + y0;
		int to = y + y0;
		while (from < to)
		{
			put_pixel(cub, -x + x0, from, 0xff0000);
			from++;
		}
		from = -y + y0;
		to = y + y0;
		while (from < to)
		{
			put_pixel(cub, x + x0, from, 0xff0000);
			from++;
		}
	}

	// clear buf
	for (int i = 0; i < 240; i++) {
		for (int j = 0; j < 240; j++) {
			cub->minimap->buf[i][j] = 0xbccddb;
		}
	}
}
