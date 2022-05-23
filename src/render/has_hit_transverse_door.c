/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_hit_transverse_door.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:10:56 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 18:16:13 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static bool	is_transverse_door(t_raycastvar *lvar, t_cub *cub)
{
	return (
		cub->map->map[lvar->map_x][lvar->map_y].side == TRANSVERSE
	);
}

static bool	has_hit_north_or_south_side(t_raycastvar *lvar)
{
	return (
		lvar->side == NORTH || lvar->side == SOUTH
	);
}

static bool	has_hit_ray_in_y(t_raycastvar *lvar, t_cub *cub, double rayhead_y)
{
	t_cell	**map;

	map = cub->map->map;
	if ((int)rayhead_y != lvar->map_y)
		return (false);
	return (
		(int)(rayhead_y - map[lvar->map_x][lvar->map_y].timer) == lvar->map_y
	);
}

static double	calc_rayhead_y(t_raycastvar *lvar, t_cub *cub)
{
	return (
		cub->player->pos_y + lvar->perp_wall_dist * lvar->ray_dir_y
	);
}

bool	has_hit_transverse_door(t_raycastvar *lvar, t_cub *cub)
{
	double		half_step_x;
	double		half_step_y;
	double		ray_head_y;
	double		added_half_step_y;

	if (is_transverse_door(lvar, cub))
	{
		if (has_hit_north_or_south_side(lvar))
		{
			half_step_x = 0.5f;
			if (lvar->ray_dir_x > 0)
				half_step_x = -0.5f;
			half_step_y = (lvar->ray_dir_y / lvar->ray_dir_x) * half_step_x;
			set_perpdist(lvar, cub);
			ray_head_y = calc_rayhead_y(lvar, cub);
			added_half_step_y = ray_head_y - half_step_y;
			if (has_hit_ray_in_y(lvar, cub, added_half_step_y))
			{
				lvar->side_dist_x += lvar->delta_dist_x * (0.5f);
				return (true);
			}
		}
	}
	return (false);
}
