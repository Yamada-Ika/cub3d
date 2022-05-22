/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:34:48 by kkaneko           #+#    #+#             */
/*   Updated: 2022/05/23 01:58:12 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	fill_buf(t_cub *cub)
{
	t_map			*map_info;
	t_player		*player;
	int				i;
	int				j;
	int				trans_i;
	int				trans_j;
	unsigned int	color;

	map_info = cub->map;
	player = cub->player;
	i = -1;
	while (++i < 240)
	{
		j = -1;
		while (++j < 240)
		{
			trans_i = i / 20 + player->pos_x - 6;
			trans_j = j / 20 + player->pos_y - 6;
			if (trans_i < 0 || trans_i >= map_info->heigth
				|| trans_j < 0 || trans_j >= map_info->width)
				continue;
			if (map_info->map[trans_i][trans_j].kind == NONE
				|| map_info->map[trans_i][trans_j].kind == DOOR && map_info->map[trans_i][trans_j].door_state == OPEN)
				color = 0x003f8e;
			else
				color = 0xbccddb;
			cub->minimap->buf[i][j] = color;
		}
	}
}

unsigned int	get_minimap_color(t_cub *cub, int x, int y)
{
	return (cub->minimap->buf[x][y]);
}

unsigned int	get_player_color(t_cub *cub, int x, int y)
{
	(void *)cub;
	(void *)x;
	(void *)y;
	return (0xff0000);
}

void	draw_circle(t_cub *cub, int r, unsigned int (*f(t_cub *, int, int)))
{
	int	x;
	int	y;
	int	from;
	int	to;

	x = -1;
	while (++x < r)
	{
		y = sqrt(r * r - x * x);
		from = -y + MINIMAP_CENTER_Y - 1;
		to = y + MINIMAP_CENTER_Y;
		while (++from < to)
			put_pixel(cub, -x + MINIMAP_CENTER_X, from, (*f)(cub, from, -x + MINIMAP_CENTER_X));
		from = -y + MINIMAP_CENTER_Y - 1;
		to = y + MINIMAP_CENTER_Y;
		while (++from < to)
			put_pixel(cub, x + MINIMAP_CENTER_X, from, (*f)(cub, from, x + MINIMAP_CENTER_X));
	}
}

void	draw_minimap(t_cub *cub)
{
	fill_buf(cub);
	draw_circle(cub, MINIMAP_SIZE / 2, get_minimap_color);
	draw_circle(cub, 10, get_player_color);
}
