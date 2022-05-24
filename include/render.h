/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:08:51 by kkaneko           #+#    #+#             */
/*   Updated: 2022/05/25 02:02:30 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"

# define MINIMAP_SIZE 240
# define MINIMAP_CENTER_X 120
# define MINIMAP_CENTER_Y 120
# define ELEVATION_LIMIT 10

typedef struct s_raycastvar
{
	int			x;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	double		half_step_x;
	double		half_step_y;
	double		euclid_dist;
	int			line_height;
	double		wall_x;
	int			draw_start;
	int			draw_end;
	t_texture	*tex;
	int			tex_x;
	double		tex_step;
}	t_raycastvar;

typedef struct s_spritevar
{
	double	sp_pos_x;
	double	sp_pos_y;
	double	sp_rpos_x;
	double	sp_rpos_y;
	int		idx;
	double	trans_x;
	double	trans_y;
	int		sprite_x_on_window;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_x;
	int		draw_start_y;
	int		draw_end_x;
	int		draw_end_y;
	int		frame_index;
	double	step_sprite_tex_x;
	double	step_sprite_tex_y;
	double	itr_x;
	double	itr_y;
	double	delta_x;
	double	delta_y;
}	t_spritevar;

typedef enum e_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}	t_side;

void		set_ray_dirction(t_raycastvar *lvar, t_cub *cub);
void		set_raycast_iterator(t_raycastvar *lvar, t_cub *cub);
void		cast_ray(t_raycastvar *lvar, t_cub *cub);
void		set_perpdist(t_raycastvar *lvar, t_cub *cub);
void		update_doorstate(t_cub *cub);
void		sort_sprites(t_cub *cub);
void		move_sprites(t_cub *cub);
void		set_wall_texture(t_raycastvar *lvar, t_cub *cub);
void		draw_vertilcal_line(t_raycastvar *lvar, t_cub *cub);

// vector getter wrapper
int			get_sprite_width(t_cub *cub, t_spritevar *lvar);
int			get_sprite_height(t_cub *cub, t_spritevar *lvar);

void		draw_minimap(t_cub *cub);
void		draw_walls(t_cub *cub);
void		draw_sprites(t_cub *cub);
void		move_sprites(t_cub *cub);
void		init_sprite_texture_iterator(t_cub *cub, t_spritevar *lvar);
void		draw_sprite(t_cub *cub, t_spritevar *lvar);
void		update_frame_index(t_cub *cub, t_spritevar *lvar);
bool		should_draw_sprite(t_cub *cub, t_spritevar *lvar, int x);
bool		has_hit_longitudinal_door(t_raycastvar *lvar, t_cub *cub);
bool		has_hit_transverse_door(t_raycastvar *lvar, t_cub *cub);
void		fill_minimap_buf(t_cub *cub);

// mlx wrapper
void		put_pixel(t_cub *cub, int x, int y, unsigned int color);
void		put_image(t_cub *cub);
int			get_texture_color(const t_texture *tex, const int x, const int y);

#endif
