/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:04 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 16:06:02 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// void	dump_lvar(t_raycastvar *lvar)
// {
// 	if (lvar->x == WIN_W / 2) {
// 		fprintf(stderr, "-- dump lvar in render --\n");
// 		fprintf(stderr, "euclid_dist    %lf\n", lvar->euclid_dist);
// 		fprintf(stderr, "perp_wall_dist %lf\n", lvar->perp_wall_dist);
// 		fprintf(stderr, "wall_x         %lf\n", lvar->wall_x);
// 	}
// }

void	set_perpbuf(t_raycastvar *lvar, t_cub *cub)
{
	cub->sprite->buf_perp[lvar->x] = lvar->perp_wall_dist;
}

void	set_draw_range(t_raycastvar *lvar, t_cub *cub)
{
	lvar->line_height = (int)(WIN_H / lvar->perp_wall_dist);
	lvar->draw_start = -lvar->line_height / 2 + WIN_H / 2 + cub->camera->pitch;
	if (lvar->draw_start < 0)
		lvar->draw_start = 0;
	lvar->draw_end = lvar->line_height / 2 + WIN_H / 2 + cub->camera->pitch;
	if (lvar->draw_end >= WIN_H)
		lvar->draw_end = WIN_H - 1;
}

static double	formed_angle(t_player *player, t_raycastvar *lvar)
{
	double	inner;
	double	norm1;
	double	norm2;

	inner = player->dir_x * lvar->ray_dir_x + player->dir_y * lvar->ray_dir_y;
	norm1 = sqrt(player->dir_x * player->dir_x
			+ player->dir_y * player->dir_y);
	norm2 = sqrt(lvar->ray_dir_x * lvar->ray_dir_x
			+ lvar->ray_dir_y * lvar->ray_dir_y);
	return (acos(inner / (norm1 * norm2)));
}

void	set_perpdist(t_raycastvar *lvar, t_cub *cub)
{
	t_player	*player;

	player = cub->player;
	if (lvar->side == NORTH || lvar->side == SOUTH)
		lvar->euclid_dist = lvar->side_dist_x - lvar->delta_dist_x;
	else
		lvar->euclid_dist = lvar->side_dist_y - lvar->delta_dist_y;
	lvar->perp_wall_dist = lvar->euclid_dist * cos(formed_angle(player, lvar));
	if (lvar->x == WIN_W / 2)
		lvar->perp_wall_dist = lvar->euclid_dist;
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
