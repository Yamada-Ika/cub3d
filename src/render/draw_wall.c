/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:04 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 01:58:05 by iyamada          ###   ########.fr       */
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

void	draw_vertilcal_line(t_raycastvar *lvar, t_cub *cub)
{
	int				i;
	double			itr_tex_y;
	unsigned int	color;
	int				tex_y;

	i = -1;
	while (++i < lvar->draw_start)
		put_pixel(cub, lvar->x, i, cub->map->ceil);
	itr_tex_y = 0.0;
	if (-lvar->line_height / 2 + WIN_H / 2 + cub->camera->pitch < 0)
		itr_tex_y += abs(-lvar->line_height / 2 + WIN_H / 2 + cub->camera->pitch) * lvar->tex_step;
	i = lvar->draw_start - 1;
	while (++i < lvar->draw_end)
	{
		tex_y = (int)itr_tex_y;
		color = get_texture_color(lvar->tex, lvar->tex_x, tex_y);
		if (lvar->side == EAST || lvar->side == SOUTH)
			color = (color >> 1) & 0b011111110111111101111111; // be darker
		put_pixel(cub, lvar->x, i, color);
		itr_tex_y += lvar->tex_step;
	}
	i = lvar->draw_end - 1;
	while (++i < WIN_H)
		put_pixel(cub, lvar->x, i, cub->map->floor);
}

void	set_wall_texture(t_raycastvar *lvar, t_cub *cub)
{
	t_player	*player;
	t_map		*map;
	double		tex_x_on_map;

	player = cub->player;
	map = cub->map;
	if(lvar->side == NORTH || lvar->side == SOUTH)
		lvar->wall_x = player->pos_y + lvar->perp_wall_dist * lvar->ray_dir_y;
	else
		lvar->wall_x = player->pos_x + lvar->perp_wall_dist * lvar->ray_dir_x;
	if (lvar->side == WEST)
	{
		lvar->tex = map->west;
		tex_x_on_map = lvar->wall_x - (int)lvar->wall_x;
	}
	else if (lvar->side == EAST)
	{
		lvar->tex = map->east;
		tex_x_on_map = (1.0 - (lvar->wall_x - (int)lvar->wall_x));
	}
	else if (lvar->side == SOUTH)
	{
		lvar->tex = map->south;
		tex_x_on_map = lvar->wall_x - (int)lvar->wall_x;
	}
	else if (lvar->side == NORTH)
	{
		lvar->tex = map->north;
		tex_x_on_map = (1.0 - (lvar->wall_x - (int)lvar->wall_x));
	}
	lvar->tex_x = lvar->tex->width * tex_x_on_map;
	lvar->tex_step = lvar->tex->height / (double)lvar->line_height;
}

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

static double	angle_formed_by(t_player *player, t_raycastvar *lvar)
{
	double	inner;
	double	norm1;
	double	norm2;

	inner = player->dir_x * lvar->ray_dir_x + player->dir_y * lvar->ray_dir_y;
	norm1 = sqrt(player->dir_x * player->dir_x + player->dir_y * player->dir_y);
	norm2 = sqrt(lvar->ray_dir_x * lvar->ray_dir_x + lvar->ray_dir_y * lvar->ray_dir_y);
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
	lvar->perp_wall_dist = lvar->euclid_dist * cos(angle_formed_by(player, lvar));
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
		// dump_lvar(&lvar);
	}
}
