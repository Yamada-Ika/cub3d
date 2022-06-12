/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:29:03 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 15:11:18 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static bool	is_nobarricade_in_x(t_cub *cub, t_spritevar *lvar, int idx)
{
	t_cell		**map;
	t_sprite	*sprites;
	int			pos_x;
	int			pos_y;

	sprites = cub->sprite->sprites;
	map = cub->map->map;
	pos_x = (int)(sprites[idx].x + lvar->delta_x);
	pos_y = (int)sprites[idx].y;
	return (
		map[pos_x][pos_y].kind == NONE
	);
}

static bool	is_nobarricade_in_y(t_cub *cub, t_spritevar *lvar, int idx)
{
	t_cell		**map;
	t_sprite	*sprites;
	int			pos_x;
	int			pos_y;

	sprites = cub->sprite->sprites;
	map = cub->map->map;
	pos_x = (int)sprites[idx].x;
	pos_y = (int)(sprites[idx].y + lvar->delta_y);
	return (
		map[pos_x][pos_y].kind == NONE
	);
}

void	move_sprites(t_cub *cub)
{
	t_sprite	*sprites;
	t_player	*player;
	t_spritevar	lvar;
	int			i;

	sprites = cub->sprite->sprites;
	player = cub->player;
	i = -1;
	while (++i < cub->sprite->num)
	{
		if (sprites[i].dist_from_player > 10.0)
			continue ;
		lvar.sp_rpos_x = player->pos_x - sprites[i].x;
		lvar.sp_rpos_y = player->pos_y - sprites[i].y;
		lvar.delta_x = lvar.sp_rpos_x * SP_MOVE_STEP;
		lvar.delta_y = lvar.sp_rpos_y * SP_MOVE_STEP;
		if (is_nobarricade_in_x(cub, &lvar, i))
			sprites[i].x += lvar.delta_x;
		if (is_nobarricade_in_y(cub, &lvar, i))
			sprites[i].y += lvar.delta_y;
	}
}
