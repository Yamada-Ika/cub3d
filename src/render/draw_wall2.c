/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:07 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 01:58:07 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	set_ray_dirction(t_raycastvar *lvar, t_cub *cub)
{
	t_player	*player;

	player = cub->player;
	lvar->camera_x = 2 * lvar->x / (double)WIN_W - 1;
	lvar->ray_dir_x = player->dir_x + player->plane_x * lvar->camera_x;
	lvar->ray_dir_y = player->dir_y + player->plane_y * lvar->camera_x;
}

static void	set_map_point(t_raycastvar *lvar, t_cub *cub)
{
	t_player		*player;

	player = cub->player;
	lvar->map_x = (int)(player->pos_x);
	lvar->map_y = (int)(player->pos_y);
}

static void	set_delta_dist(t_raycastvar *lvar, t_cub *cub)
{
	lvar->delta_dist_x = sqrt(1 + (lvar->ray_dir_y * lvar->ray_dir_y) / (lvar->ray_dir_x * lvar->ray_dir_x));
	lvar->delta_dist_y = sqrt(1 + (lvar->ray_dir_x * lvar->ray_dir_x) / (lvar->ray_dir_y * lvar->ray_dir_y));
}

void	set_raycast_iterator(t_raycastvar *lvar, t_cub *cub)
{
	t_player		*player;

	player = cub->player;
	set_map_point(lvar, cub);
	set_delta_dist(lvar, cub);
	if (lvar->ray_dir_x < 0)
	{
		lvar->step_x = -1;
		lvar->side_dist_x = (player->pos_x - lvar->map_x) * lvar->delta_dist_x;
	}
	else
	{
		lvar->step_x = 1;
		lvar->side_dist_x = (lvar->map_x + 1.0 - player->pos_x) * lvar->delta_dist_x;
	}
	if (lvar->ray_dir_y < 0)
	{
		lvar->step_y = -1;
		lvar->side_dist_y = (player->pos_y - lvar->map_y) * lvar->delta_dist_y;
	}
	else
	{
		lvar->step_y = 1;
		lvar->side_dist_y = (lvar->map_y + 1.0 - player->pos_y) * lvar->delta_dist_y;
	}
}
