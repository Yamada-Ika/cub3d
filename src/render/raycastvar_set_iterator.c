/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastvar_set_iterator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:29:07 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 16:29:35 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	set_map_point(t_raycastvar *lvar, t_cub *cub)
{
	t_player	*player;

	player = cub->player;
	lvar->map_x = (int)(player->pos_x);
	lvar->map_y = (int)(player->pos_y);
}

static void	set_delta_dist(t_raycastvar *lvar, t_cub *cub)
{
	double	power_x;
	double	power_y;

	power_x = lvar->ray_dir_x * lvar->ray_dir_x;
	power_y = lvar->ray_dir_y * lvar->ray_dir_y;
	lvar->delta_dist_x = sqrt(1 + power_y / power_x);
	lvar->delta_dist_y = sqrt(1 + power_x / power_y);
}

static void	set_raycast_iterator_in_x(t_raycastvar *lvar, t_cub *cub)
{
	t_player	*player;

	player = cub->player;
	if (lvar->ray_dir_x < 0)
	{
		lvar->step_x = -1;
		lvar->side_dist_x = (player->pos_x - lvar->map_x)
			* lvar->delta_dist_x;
	}
	else
	{
		lvar->step_x = 1;
		lvar->side_dist_x = (lvar->map_x + 1.0 - player->pos_x)
			* lvar->delta_dist_x;
	}
}

static void	set_raycast_iterator_in_y(t_raycastvar *lvar, t_cub *cub)
{
	t_player	*player;

	player = cub->player;
	if (lvar->ray_dir_y < 0)
	{
		lvar->step_y = -1;
		lvar->side_dist_y = (player->pos_y - lvar->map_y)
			* lvar->delta_dist_y;
	}
	else
	{
		lvar->step_y = 1;
		lvar->side_dist_y = (lvar->map_y + 1.0 - player->pos_y)
			* lvar->delta_dist_y;
	}
}

void	set_raycast_iterator(t_raycastvar *lvar, t_cub *cub)
{
	t_player	*player;

	player = cub->player;
	set_map_point(lvar, cub);
	set_delta_dist(lvar, cub);
	set_raycast_iterator_in_x(lvar, cub);
	set_raycast_iterator_in_y(lvar, cub);
}
