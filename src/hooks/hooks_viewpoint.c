/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_viewpoint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:37:49 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 21:52:44 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

void	move_viewpoint(t_cub *cub, int keycode)
{
	t_player	*player;

	player = cub->player;
	if (keycode == R_ARROW)
	{
		rotate_2d(&player->dir_x, &player->dir_y, ROT_STEP);
		rotate_2d(&player->plane_x, &player->plane_y, ROT_STEP);
		return ;
	}
	if (keycode == L_ARROW)
	{
		rotate_2d(&player->dir_x, &player->dir_y, -ROT_STEP);
		rotate_2d(&player->plane_x, &player->plane_y, -ROT_STEP);
		return ;
	}
}
