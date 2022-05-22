/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:10 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 01:58:10 by iyamada          ###   ########.fr       */
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

static bool	has_hit_longitudinal_door(t_raycastvar *lvar, t_cub *cub)
{
	t_player	*player;
	t_map		*map;
	double		half_step_x;
	double		half_step_y;
	double		ray_head_x;
	double		added_half_step_x;

	player = cub->player;
	map = cub->map;
	if (map->map[lvar->map_x][lvar->map_y].side == LONGITUDINAL)
	{
		if (lvar->side == EAST || lvar->side == WEST)
		{
			half_step_y = 0.5f;
			if (lvar->ray_dir_y > 0)
				half_step_y = -0.5f;
			half_step_x = (lvar->ray_dir_x / lvar->ray_dir_y) * half_step_y;
			set_perpdist(lvar, cub);
			ray_head_x = player->pos_x + lvar->perp_wall_dist * lvar->ray_dir_x;
			added_half_step_x = ray_head_x - half_step_x;
			if ((int)added_half_step_x != lvar->map_x)
				return (false);
			if ((int)(added_half_step_x - map->map[lvar->map_x][lvar->map_y].timer) == lvar->map_x)
			{
				lvar->side_dist_y += lvar->delta_dist_y * (0.5f);
				return (true);
			}
		}
	}
	return (false);
}

static bool	has_hit_transverse_door(t_raycastvar *lvar, t_cub *cub)
{
	t_player	*player;
	t_map		*map;
	double		half_step_x;
	double		half_step_y;
	double		ray_head_y;
	double		added_half_step_y;

	player = cub->player;
	map = cub->map;
	if (map->map[lvar->map_x][lvar->map_y].side == TRANSVERSE)
	{
		if (lvar->side == NORTH || lvar->side == SOUTH)
		{
			half_step_x = 0.5f;
			if (lvar->ray_dir_x > 0)
				half_step_x = -0.5f;
			half_step_y = (lvar->ray_dir_y / lvar->ray_dir_x) * half_step_x;
			set_perpdist(lvar, cub);
			ray_head_y = player->pos_y + lvar->perp_wall_dist * lvar->ray_dir_y;
			added_half_step_y = ray_head_y - half_step_y;
			if ((int)added_half_step_y != lvar->map_y)
				return (false);
			if ((int)(added_half_step_y - map->map[lvar->map_x][lvar->map_y].timer) == lvar->map_y)
			{
				lvar->side_dist_x += lvar->delta_dist_x * (0.5f);
				return (true);
			}
		}
	}
	return (false);
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
