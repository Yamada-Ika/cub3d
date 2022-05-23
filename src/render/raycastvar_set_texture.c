/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastvar_set_texture.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:01:23 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 20:38:32 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	set_ray_collide_pos(t_raycastvar *lvar, t_cub *cub)
{
	t_player	*player;

	player = cub->player;
	if (lvar->side == NORTH || lvar->side == SOUTH)
		lvar->wall_x = player->pos_y + lvar->perp_wall_dist * lvar->ray_dir_y;
	else
		lvar->wall_x = player->pos_x + lvar->perp_wall_dist * lvar->ray_dir_x;
}

static t_texture	*get_texture(t_cub *cub, t_raycastvar *lvar)
{
	if (lvar->side == WEST)
		return (cub->map->west);
	if (lvar->side == EAST)
		return (cub->map->east);
	if (lvar->side == NORTH)
		return (cub->map->north);
	if (lvar->side == SOUTH)
		return (cub->map->south);
}

static double	calc_texture_x_on_map(t_cub *cub, t_raycastvar *lvar)
{
	if (lvar->side == WEST)
		return (lvar->wall_x - (int)lvar->wall_x);
	if (lvar->side == EAST)
		return (1.0 - (lvar->wall_x - (int)lvar->wall_x));
	if (lvar->side == SOUTH)
		return (lvar->wall_x - (int)lvar->wall_x);
	if (lvar->side == NORTH)
		return (1.0 - (lvar->wall_x - (int)lvar->wall_x));
}

static void	set_ray_collide_pos_on_tex(t_raycastvar *lvar, t_cub *cub)
{
	double	tex_x_on_map;

	lvar->tex = get_texture(cub, lvar);
	tex_x_on_map = calc_texture_x_on_map(cub, lvar);
	lvar->tex_x = lvar->tex->width * tex_x_on_map;
	lvar->tex_step = lvar->tex->height / (double)lvar->line_height;
}

void	set_wall_texture(t_raycastvar *lvar, t_cub *cub)
{
	set_ray_collide_pos(lvar, cub);
	set_ray_collide_pos_on_tex(lvar, cub);
}
