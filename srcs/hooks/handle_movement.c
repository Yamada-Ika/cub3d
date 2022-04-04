/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:20:07 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/03 00:09:54 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_movement(int keycode, t_game *game)
{
	int	fg_re_render;

	fg_re_render = 1;
	if (keycode == W_KEY)
		move_straight(game->player);
	else if (keycode == A_KEY)
		move_left(game->player);
	else if (keycode == S_KEY)
		move_back(game->player);
	else if (keycode == D_KEY)
		move_right(game->player);
	else
		fg_re_render = 0;
	return (fg_re_render);
}

void	move_straight(t_player *player)
{
	t_affine	*move_dir;

	move_dir = mat_affine_new(2);
	move_dir->vector = mat_rotation_2d_new(0, player->dir);
	mat_zoom_2d(MOVE_STEP, MOVE_STEP, move_dir);
	mat_translation_2d(move_dir->vector->values[0][0],
						move_dir->vector->values[1][0],
						player->pos);
	mat_affine_free(&move_dir);
}

void	move_left(t_player *player)
{
	t_affine	*move_dir;

	move_dir = mat_affine_new(2);
	move_dir->vector = mat_rotation_2d_new(-M_PI_2, player->dir);
	mat_zoom_2d(MOVE_STEP, MOVE_STEP, move_dir);
	mat_translation_2d(move_dir->vector->values[0][0],
						move_dir->vector->values[1][0],
						player->pos);
	mat_affine_free(&move_dir);
}

void	move_right(t_player *player)
{
	t_affine	*move_dir;

	move_dir = mat_affine_new(2);
	move_dir->vector = mat_rotation_2d_new(M_PI_2, player->dir);
	mat_zoom_2d(MOVE_STEP, MOVE_STEP, move_dir);
	mat_translation_2d(move_dir->vector->values[0][0],
						move_dir->vector->values[1][0],
						player->pos);
	mat_affine_free(&move_dir);
}

void	move_back(t_player *player)
{
	t_affine	*move_dir;

	move_dir = mat_affine_new(2);
	move_dir->vector = mat_rotation_2d_new(M_PI, player->dir);;
	mat_zoom_2d(MOVE_STEP, MOVE_STEP, move_dir);
	mat_translation_2d(move_dir->vector->values[0][0],
						move_dir->vector->values[1][0],
						player->pos);
	mat_affine_free(&move_dir);
}

