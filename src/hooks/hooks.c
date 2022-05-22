/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:32:33 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 02:38:56 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

static void	update_doorstate(t_cub *cub, int keycode)
{
	t_cell		**map;
	t_player	*player;

	map = cub->map->map;
	player = cub->player;
	if (keycode == SPACE)
	{
		double	pos_x = player->pos_x + player->dir_x * 1.0;
		double	pos_y = player->pos_y + player->dir_y * 1.0;

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

static bool	should_move_viewpoint(int keycode)
{
	return (
		keycode == R_ARROW
		|| keycode == L_ARROW
		|| keycode == U_ARROW
		|| keycode == D_ARROW
	);
}

static bool	should_update_doorstate(int keycode)
{
	return (
		keycode == SPACE
	);
}

static int	handle_key_hook(int keycode, void *params)
{
	t_cub	*cub;

	cub = (t_cub *)params;
	if (keycode == ESC)
		exit(0);
	if (should_move_player(keycode))
	{
		move_player(cub, keycode);
		return (0);
	}
	if (should_move_viewpoint(keycode))
	{
		move_viewpoint(cub, keycode);
		return (0);
	}
	if (should_update_doorstate(keycode))
	{
		update_doorstate(cub, keycode);
		return (0);
	}
	return (0);
}

void	install_event_hooks(t_cub *cub)
{
	mlx_hook(cub->window->mlx_win, KeyPress, KeyPressMask, handle_key_hook, cub);
	mlx_loop_hook(cub->window->mlx, render, cub);
}
