/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:04 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 21:43:31 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	set_perpbuf(t_raycastvar *lvar, t_cub *cub)
{
	cub->sprite->buf_perp[lvar->x] = lvar->perp_wall_dist;
}

static void	set_draw_range(t_raycastvar *lvar, t_cub *cub)
{
	double	delta_h;

	delta_h = cub->camera->pitch
		+ cub->player->elevation / lvar->perp_wall_dist;
	lvar->line_height = (int)(WIN_H / lvar->perp_wall_dist);
	lvar->draw_start = -lvar->line_height / 2 + WIN_H / 2 + delta_h;
	if (lvar->draw_start < 0)
		lvar->draw_start = 0;
	lvar->draw_end = lvar->line_height / 2 + WIN_H / 2 + delta_h;
	if (lvar->draw_end >= WIN_H)
		lvar->draw_end = WIN_H - 1;
}

void	draw_walls(t_cub *cub)
{
	t_raycastvar	lvar;

	lvar.x = -1;
	while (++lvar.x < WIN_W)
	{
		set_ray_dirction(&lvar, cub);
		set_raycast_iterator(&lvar, cub);
		cast_ray(&lvar, cub);
		set_perpdist(&lvar, cub);
		set_draw_range(&lvar, cub);
		set_wall_texture(&lvar, cub);
		draw_vertilcal_line(&lvar, cub);
		set_perpbuf(&lvar, cub);
	}
}
