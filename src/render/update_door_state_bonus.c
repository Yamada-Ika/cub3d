/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_door_state_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:42:40 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 15:10:26 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static bool	is_door_open_or_close(t_cub *cub, t_point *p)
{
	t_cell	**map;

	map = cub->map->map;
	return (
		map[p->x][p->y].door_state == OPEN
		|| map[p->x][p->y].door_state == CLOSE
	);
}

static void	update_open_door_state(t_cub *cub, t_point *p, double timespan)
{
	t_cell	**map;

	map = cub->map->map;
	map[p->x][p->y].timer += timespan;
	if (map[p->x][p->y].timer < 0.0)
		map[p->x][p->y].timer = 0.0;
	if (map[p->x][p->y].timer > 1.0)
	{
		map[p->x][p->y].timer = 1.0;
		map[p->x][p->y].door_state = OPEN;
	}
}

static void	update_close_door_state(t_cub *cub, t_point *p, double timespan)
{
	t_cell	**map;

	map = cub->map->map;
	map[p->x][p->y].timer -= timespan;
	if (map[p->x][p->y].timer > 1.0)
		map[p->x][p->y].timer = 1.0;
	if (map[p->x][p->y].timer < 0.0)
	{
		map[p->x][p->y].timer = 0.0;
		map[p->x][p->y].door_state = CLOSE;
	}
}

void	update_doorstate(t_cub *cub)
{
	t_cell	**map;
	t_point	*p;
	double	timespan;
	int		i;

	map = cub->map->map;
	i = -1;
	while (++i < cub->map->door_points->len)
	{
		p = (t_point *)vec_at(cub->map->door_points, i);
		if (is_door_open_or_close(cub, p))
			continue ;
		timespan = (gettimestamp() - cub->timestamp) / 100.0;
		if (map[p->x][p->y].door_state == OPENING)
			update_open_door_state(cub, p, timespan);
		if (map[p->x][p->y].door_state == CLOSING)
			update_close_door_state(cub, p, timespan);
	}
}
