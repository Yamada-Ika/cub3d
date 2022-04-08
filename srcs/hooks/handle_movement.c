/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:20:07 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/06 15:49:29 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_straight(t_player *player, t_map *map);
static void	move_left(t_player *player, t_map *map);
static void	move_right(t_player *player, t_map *map);
static void	move_back(t_player *player, t_map *map);

int	handle_movement(int keycode, t_game *game)
{
	int	fg_re_render;

	fg_re_render = 1;
	if (keycode == W_KEY)
		move_straight(game->player, game->map);
	else if (keycode == A_KEY)
		move_left(game->player, game->map);
	else if (keycode == S_KEY)
		move_back(game->player, game->map);
	else if (keycode == D_KEY)
		move_right(game->player, game->map);
	else
		fg_re_render = 0;
	return (fg_re_render);
}

/*
posを計算して、wallと衝突しているか判定。衝突していなかったらおk。していたら、posを戻して何もしない
*/

t_affine	*dup_affine(t_affine *org)
{
	t_affine	*new;

	new = mat_affine_new(2);
	new->vector = mat_dup(org->vector);
	return (new);
}

bool	will_collide_helper(t_player *player, t_map *map, double rotate_angle)
{
	t_affine	*move_dir;
	t_affine	*dup_pos;
	bool		is_collision;

	if (map->map->values[(int)mat_get_y(player->pos->vector)][(int)mat_get_x(player->pos->vector)] > 0)
		return (true);

	move_dir = mat_affine_new(2);
	move_dir->vector = mat_rotation_2d_new(rotate_angle, player->dir);
	mat_zoom_2d(MOVE_STEP, MOVE_STEP, move_dir);
	dup_pos = dup_affine(player->pos);
	mat_translation_2d(move_dir->vector->values[0][0],
						move_dir->vector->values[1][0],
						dup_pos);

	is_collision = false;
	if (map->map->values[(int)mat_get_y(dup_pos->vector)][(int)mat_get_x(dup_pos->vector)] > 0)
		is_collision = true;

	mat_affine_free(&move_dir);
	mat_affine_free(&dup_pos);
	return (is_collision);
}

bool	will_collide_stratight(t_player *player, t_map *map)
{
	return (will_collide_helper(player, map, 0));
}

bool	will_collide_left(t_player *player, t_map *map)
{
	return (will_collide_helper(player, map, -M_PI_2));
}

bool	will_collide_right(t_player *player, t_map *map)
{
	return (will_collide_helper(player, map, M_PI_2));
}

bool	will_collide_back(t_player *player, t_map *map)
{
	return (will_collide_helper(player, map, M_PI));
}

static void	move_straight(t_player *player, t_map *map)
{
	t_affine	*move_dir;

	if (!will_collide_stratight(player, map))
	{
		move_dir = mat_affine_new(2);
		move_dir->vector = mat_rotation_2d_new(0, player->dir);
		mat_zoom_2d(MOVE_STEP, MOVE_STEP, move_dir);
		mat_translation_2d(move_dir->vector->values[0][0],
							move_dir->vector->values[1][0],
							player->pos);
		mat_affine_free(&move_dir);
	}
}

void	move_left(t_player *player, t_map *map)
{
	t_affine	*move_dir;

	if (!will_collide_left(player, map))
	{
		move_dir = mat_affine_new(2);
		move_dir->vector = mat_rotation_2d_new(-M_PI_2, player->dir);
		mat_zoom_2d(MOVE_STEP, MOVE_STEP, move_dir);
		mat_translation_2d(move_dir->vector->values[0][0],
							move_dir->vector->values[1][0],
							player->pos);
		mat_affine_free(&move_dir);
	}
}

void	move_right(t_player *player, t_map *map)
{
	t_affine	*move_dir;

	if (!will_collide_right(player, map))
	{
		move_dir = mat_affine_new(2);
		move_dir->vector = mat_rotation_2d_new(M_PI_2, player->dir);
		mat_zoom_2d(MOVE_STEP, MOVE_STEP, move_dir);
		mat_translation_2d(move_dir->vector->values[0][0],
							move_dir->vector->values[1][0],
							player->pos);
		mat_affine_free(&move_dir);
	}
}

void	move_back(t_player *player, t_map *map)
{
	t_affine	*move_dir;

	if (!will_collide_back(player, map))
	{
		move_dir = mat_affine_new(2);
		move_dir->vector = mat_rotation_2d_new(M_PI, player->dir);;
		mat_zoom_2d(MOVE_STEP, MOVE_STEP, move_dir);
		mat_translation_2d(move_dir->vector->values[0][0],
							move_dir->vector->values[1][0],
							player->pos);
		mat_affine_free(&move_dir);
	}
}

