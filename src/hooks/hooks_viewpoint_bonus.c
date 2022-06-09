/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_viewpoint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:37:49 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 02:38:31 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

void	rotate_2d(double *a, double *b, double angle)
{
	double	tmp_a;
	double	tmp_b;

	tmp_a = (*a) * cos(angle) + (*b) * sin(angle);
	tmp_b = -(*a) * sin(angle) + (*b) * cos(angle);
	*a = tmp_a;
	*b = tmp_b;
}

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
	if (keycode == U_ARROW)
	{
		cub->camera->pitch += 10.0;
		return ;
	}
	if (keycode == D_ARROW)
	{
		cub->camera->pitch += -10.0;
		return ;
	}
}
