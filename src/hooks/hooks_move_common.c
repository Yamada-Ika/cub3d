/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 09:57:50 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 09:58:11 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

static bool	can_move(const t_cub *cub, const double x, const double y)
{
	t_cell	**map;

	map = cub->map->map;
	return (
		map[(int)x][(int)y].kind == WALL
		|| (map[(int)x][(int)y].kind == DOOR
			&& map[(int)x][(int)y].door_state == CLOSE)
	);
}

void	move_front(t_cub *cub)
{
	t_player	*p;

	p = cub->player;
	if (can_move(cub, p->pos_x, p->pos_y + p->dir_y * MOVE_STEP))
		return ;
	p->pos_y += p->dir_y * MOVE_STEP;
	if (can_move(cub, p->pos_x + p->dir_x * MOVE_STEP, p->pos_y))
		return ;
	p->pos_x += p->dir_x * MOVE_STEP;
}

void	move_back(t_cub *cub)
{
	t_player	*p;

	p = cub->player;
	if (can_move(cub, p->pos_x, p->pos_y - p->dir_y * MOVE_STEP))
		return ;
	p->pos_y -= p->dir_y * MOVE_STEP;
	if (can_move(cub, p->pos_x - p->dir_x * MOVE_STEP, p->pos_y))
		return ;
	p->pos_x -= p->dir_x * MOVE_STEP;
}

void	move_left(t_cub *cub)
{
	t_player	*p;
	double		ortho_x;
	double		ortho_y;
	double		delta_x;
	double		delta_y;

	p = cub->player;
	ortho_x = p->dir_x;
	ortho_y = p->dir_y;
	rotate_2d(&ortho_x, &ortho_y, -1.57079632679);
	delta_x = ortho_x * MOVE_STEP;
	delta_y = ortho_y * MOVE_STEP;
	if (can_move(cub, p->pos_x + delta_x, p->pos_y + delta_y))
		return ;
	p->pos_x += delta_x;
	p->pos_y += delta_y;
}

void	move_right(t_cub *cub)
{
	t_player	*p;
	double		ortho_x;
	double		ortho_y;
	double		delta_x;
	double		delta_y;

	p = cub->player;
	ortho_x = p->dir_x;
	ortho_y = p->dir_y;
	rotate_2d(&ortho_x, &ortho_y, 1.57079632679);
	delta_x = ortho_x * MOVE_STEP;
	delta_y = ortho_y * MOVE_STEP;
	if (can_move(cub, p->pos_x + delta_x, p->pos_y + delta_y))
		return ;
	p->pos_x += delta_x;
	p->pos_y += delta_y;
}
