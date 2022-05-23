/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:10 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 18:10:53 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	update_rayiterator(t_raycastvar *lvar)
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

static bool	has_hit_wall(t_raycastvar *lvar, t_cub *cub)
{
	return (
		cub->map->map[lvar->map_x][lvar->map_y].kind == WALL
	);
}

static bool	is_in_door_cell(t_raycastvar *lvar, t_cub *cub)
{
	return (
		cub->map->map[lvar->map_x][lvar->map_y].kind == DOOR
	);
}

static bool	has_hit_door(t_raycastvar *lvar, t_cub *cub)
{
	if (is_in_door_cell(lvar, cub))
	{
		if (has_hit_longitudinal_door(lvar, cub))
			return (true);
		if (has_hit_transverse_door(lvar, cub))
			return (true);
	}
	return (false);
}

void	cast_ray(t_raycastvar *lvar, t_cub *cub)
{
	while (true)
	{
		update_rayiterator(lvar);
		if (has_hit_wall(lvar, cub))
			break ;
		if (has_hit_door(lvar, cub))
			break ;
	}
}
