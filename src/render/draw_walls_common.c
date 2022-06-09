/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls_common.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:18:28 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 21:37:40 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

double	formed_angle(t_player *player, t_raycastvar *lvar)
{
	double	inner;
	double	norm1;
	double	norm2;

	inner = player->dir_x * lvar->ray_dir_x + player->dir_y * lvar->ray_dir_y;
	norm1 = sqrt(player->dir_x * player->dir_x
			+ player->dir_y * player->dir_y);
	norm2 = sqrt(lvar->ray_dir_x * lvar->ray_dir_x
			+ lvar->ray_dir_y * lvar->ray_dir_y);
	return (acos(inner / (norm1 * norm2)));
}

void	set_perpdist(t_raycastvar *lvar, t_cub *cub)
{
	t_player	*player;

	player = cub->player;
	if (lvar->side == NORTH || lvar->side == SOUTH)
		lvar->euclid_dist = lvar->side_dist_x - lvar->delta_dist_x;
	else
		lvar->euclid_dist = lvar->side_dist_y - lvar->delta_dist_y;
	lvar->perp_wall_dist = lvar->euclid_dist * cos(formed_angle(player, lvar));
	if (lvar->x == WIN_W / 2)
		lvar->perp_wall_dist = lvar->euclid_dist;
}

void	set_ray_dirction(t_raycastvar *lvar, t_cub *cub)
{
	t_player	*player;

	player = cub->player;
	lvar->camera_x = 2 * lvar->x / (double)WIN_W - 1;
	lvar->ray_dir_x = player->dir_x + player->plane_x * lvar->camera_x;
	lvar->ray_dir_y = player->dir_y + player->plane_y * lvar->camera_x;
}
