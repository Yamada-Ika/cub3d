/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 03:01:48 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 03:02:02 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

void	update_doorstate(t_cub *cub, int keycode)
{
	t_cell		**map;
	t_player	*player;
	double		pos_x;
	double		pos_y;

	map = cub->map->map;
	player = cub->player;
	if (keycode == SPACE)
	{
		pos_x = player->pos_x + player->dir_x * 1.0;
		pos_y = player->pos_y + player->dir_y * 1.0;
		if (map[(int)pos_x][(int)pos_y].kind == DOOR
			&& map[(int)pos_x][(int)pos_y].door_state == CLOSE)
		{
			map[(int)pos_x][(int)pos_y].door_state = OPENING;
			map[(int)pos_x][(int)pos_y].timer = 0.0f;
			return ;
		}
		if (map[(int)pos_x][(int)pos_y].kind == DOOR
			&& map[(int)pos_x][(int)pos_y].door_state == OPEN)
		{
			map[(int)pos_x][(int)pos_y].door_state = CLOSING;
			map[(int)pos_x][(int)pos_y].timer = 1.0f;
			return ;
		}
		return ;
	}
}
