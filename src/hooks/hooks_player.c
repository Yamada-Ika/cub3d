/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:35:48 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 02:37:21 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

static bool	is_barricade_in_front_of_player(const t_cub *cub, const double x, const double y)
{
	t_cell	**map;

	map = cub->map->map;
	return (
		map[(int)x][(int)y].kind == WALL
		|| (map[(int)x][(int)y].kind == DOOR && map[(int)x][(int)y].door_state == CLOSE)
	);
}

void	move_player(t_cub *cub, int keycode)
{
	t_cell		**map;
	t_player	*player;

	map = cub->map->map;
	player = cub->player;
	if (keycode == W_KEY)
	{
		if (is_barricade_in_front_of_player(cub, player->pos_x, player->pos_y + player->dir_y * MOVE_STEP))
			return ;
		player->pos_y += player->dir_y * MOVE_STEP;
		if (is_barricade_in_front_of_player(cub, player->pos_x + player->dir_x * MOVE_STEP, player->pos_y))
			return ;
		player->pos_x += player->dir_x * MOVE_STEP;
		return ;
	}
	if (keycode == S_KEY)
	{
		if (is_barricade_in_front_of_player(cub, player->pos_x, player->pos_y - player->dir_y * MOVE_STEP))
			return ;
		player->pos_y -= player->dir_y * MOVE_STEP;
		if (is_barricade_in_front_of_player(cub, player->pos_x - player->dir_x * MOVE_STEP, player->pos_y))
			return ;
		player->pos_x -= player->dir_x * MOVE_STEP;
		return ;
	}
	if (keycode == A_KEY)
	{
		double ortho_dir_x = player->dir_x;
		double ortho_dir_y = player->dir_y;

		rotate_2d(&ortho_dir_x, &ortho_dir_y, -1.57079632679);
		if (is_barricade_in_front_of_player(cub, player->pos_x + ortho_dir_x * MOVE_STEP, player->pos_y + ortho_dir_y * MOVE_STEP))
			return ;
		player->pos_x += ortho_dir_x * MOVE_STEP;
		player->pos_y += ortho_dir_y * MOVE_STEP;
		return ;
	}
	if (keycode == D_KEY)
	{
		double ortho_dir_x = player->dir_x;
		double ortho_dir_y = player->dir_y;
	
		rotate_2d(&ortho_dir_x, &ortho_dir_y, 1.57079632679);
		if (is_barricade_in_front_of_player(cub, player->pos_x + ortho_dir_x * MOVE_STEP, player->pos_y + ortho_dir_y * MOVE_STEP))
			return ;
		player->pos_x += ortho_dir_x * MOVE_STEP;
		player->pos_y += ortho_dir_y * MOVE_STEP;
		return ;
	}
}

bool	should_move_player(int keycode)
{
	return (
		keycode == W_KEY
		|| keycode == S_KEY
		|| keycode == A_KEY
		|| keycode == D_KEY
	);
}
