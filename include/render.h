/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:08:51 by kkaneko           #+#    #+#             */
/*   Updated: 2022/05/22 02:07:47 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include "cub3d.h"

typedef struct s_raycastvar
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	double	half_step_x;
	double	half_step_y;
	double	euclid_dist;
	int		line_height;
	double	wall_x;
	int		draw_start;
	int		draw_end;
	t_texture	*tex;
	int			tex_x;
	double		tex_step;
}	t_raycastvar;

typedef enum e_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}	t_side;

void	set_ray_dirction(t_raycastvar *lvar, t_cub *cub);
void	set_raycast_iterator(t_raycastvar *lvar, t_cub *cub);
void	cast_ray(t_raycastvar *lvar, t_cub *cub);
void	set_perpdist(t_raycastvar *lvar, t_cub *cub);

int		get_texture_color(const t_texture *tex, const int x, const int y);

#endif
