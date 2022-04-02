/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_perspective.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:24:55 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 19:33:18 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_perspective(int keycode, t_game *game)
{
	int	fg_re_render;

	fg_re_render = 1;
	if (keycode == R_ARROW)
		turn_right(game->player);
	else if (keycode == L_ARROW)
		turn_left(game->player);
	else
		fg_re_render = 0;
	return (fg_re_render);
}

void	turn_right(t_player *player)
{
	mat_rotation_2d(PERSPECT_ROT_RATE, player->dir);
}

void	turn_left(t_player *player)
{
	mat_rotation_2d(-PERSPECT_ROT_RATE, player->dir);
}
