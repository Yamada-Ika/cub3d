/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_perspective.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:24:55 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 03:59:58 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_perspective(int keycode, t_game *game)
{
	// int	fg_re_render;

	// fg_re_render = 1;
	// if (keycode == R_ARROW)
	// 	turn_right(game->player);
	// else if (keycode == L_ARROW)
	// 	turn_left(game->player);
	// else
	// 	fg_re_render = 0;
	// return (fg_re_render);
}

void	turn_right(t_player *player)
{
	t_affine	*tmp;

	tmp = mat_affine_new(2);
	tmp->vector = mat_mul_scalar_new(-1, player->pos->vector);
	mat_translation_2d(tmp->vector->values[0][0],
						tmp->vector->values[1][0],
						player->dir);
	mat_rotation_2d(-PERSPECT_ROT_RATE, player->dir);
	mat_translation_2d(player->pos->vector->values[0][0],
						player->pos->vector->values[1][0],
						player->dir);
	mat_affine_free(&tmp);
}

void	turn_left(t_player *player)
{
	t_affine	*tmp;

	tmp = mat_affine_new(2);
	tmp->vector = mat_mul_scalar_new(-1, player->pos->vector);
	mat_translation_2d(tmp->vector->values[0][0],
						tmp->vector->values[1][0],
						player->dir);
	mat_rotation_2d(PERSPECT_ROT_RATE, player->dir);
	mat_translation_2d(player->pos->vector->values[0][0],
						player->pos->vector->values[1][0],
						player->dir);
	mat_affine_free(&tmp);
}
