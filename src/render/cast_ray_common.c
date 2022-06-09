/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_common.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:10 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 21:39:36 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	update_rayiterator(t_raycastvar *lvar)
{
	if (lvar->side_dist_x < lvar->side_dist_y)
	{
		lvar->side_dist_x += lvar->delta_dist_x;
		lvar->map_x += lvar->step_x;
		if (lvar->ray_dir_x > 0)
			lvar->side = NORTH;
		else
			lvar->side = SOUTH;
	}
	else
	{
		lvar->side_dist_y += lvar->delta_dist_y;
		lvar->map_y += lvar->step_y;
		if (lvar->ray_dir_y > 0)
			lvar->side = WEST;
		else
			lvar->side = EAST;
	}
}

bool	has_hit_wall(t_raycastvar *lvar, t_cub *cub)
{
	return (
		cub->map->map[lvar->map_x][lvar->map_y].kind == WALL
	);
}
