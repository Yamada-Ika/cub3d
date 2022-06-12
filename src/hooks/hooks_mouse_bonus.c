/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 02:06:00 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/10 02:26:18 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

int	handle_mouse_hook(int x, int y, void *params)
{
	static int	prev_x = 0;
	static int	prev_y = 0;
	t_cub		*cub;
	t_player	*player;

	cub = (t_cub *)params;
	player = cub->player;
	if (prev_x - x < 0)
	{
		rotate_2d(&player->dir_x, &player->dir_y, ROT_STEP);
		rotate_2d(&player->plane_x, &player->plane_y, ROT_STEP);
	}
	else if (prev_x - x > 0)
	{
		rotate_2d(&player->dir_x, &player->dir_y, -ROT_STEP);
		rotate_2d(&player->plane_x, &player->plane_y, -ROT_STEP);
	}
	if (prev_y - y > 0)
		cub->camera->pitch += 10.0;
	else if (prev_y - y < 0)
		cub->camera->pitch += -10.0;
	prev_x = x;
	prev_y = y;
	return (0);
}
