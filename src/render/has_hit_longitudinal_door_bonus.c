/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_hit_longitudinal_door_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:09:42 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 15:11:08 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static bool	is_longitudinal_door(t_raycastvar *lvar, t_cub *cub)
{
	return (
		cub->map->map[lvar->map_x][lvar->map_y].side == LONGITUDINAL
	);
}

static bool	has_hit_east_or_west_side(t_raycastvar *lvar)
{
	return (
		lvar->side == EAST || lvar->side == WEST
	);
}

static bool	has_hit_ray_in_x(t_raycastvar *lvar, t_cub *cub, double rayhead_x)
{
	t_cell	**map;

	map = cub->map->map;
	if ((int)rayhead_x != lvar->map_x)
		return (false);
	return (
		(int)(rayhead_x - map[lvar->map_x][lvar->map_y].timer) == lvar->map_x
	);
}

static double	calc_rayhead_x(t_raycastvar *lvar, t_cub *cub)
{
	return (
		cub->player->pos_x + lvar->perp_wall_dist * lvar->ray_dir_x
	);
}

bool	has_hit_longitudinal_door(t_raycastvar *lvar, t_cub *cub)
{
	double		half_step_x;
	double		half_step_y;
	double		ray_head_x;
	double		added_half_step_x;

	if (is_longitudinal_door(lvar, cub))
	{
		if (has_hit_east_or_west_side(lvar))
		{
			half_step_y = 0.5f;
			if (lvar->ray_dir_y > 0)
				half_step_y = -0.5f;
			half_step_x = (lvar->ray_dir_x / lvar->ray_dir_y) * half_step_y;
			set_perpdist(lvar, cub);
			ray_head_x = calc_rayhead_x(lvar, cub);
			added_half_step_x = ray_head_x - half_step_x;
			if (has_hit_ray_in_x(lvar, cub, added_half_step_x))
			{
				lvar->side_dist_y += lvar->delta_dist_y * (0.5f);
				return (true);
			}
		}
	}
	return (false);
}
