/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:10 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 21:40:20 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
