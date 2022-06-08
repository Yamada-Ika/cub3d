/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:08:51 by kkaneko           #+#    #+#             */
/*   Updated: 2022/06/08 21:06:02 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "cub3d.h"

# define A 48271
# define B 0
# define M INT_MAX

typedef enum e_type_flag
{
	NORTH_PATH_FLAG = 1,
	SOUTH_PATH_FLAG,
	WEST_PATH_FLAG,
	EAST_PATH_FLAG,
	FLOOR_COLOR_FLAG,
	CEIL_COLOR_FLAG,
}	t_type_flag;

typedef enum e_tex_flag
{
	NORTH_FLAG = 1,
	SOUTH_FLAG,
	WEST_FLAG,
	EAST_FLAG,
}	t_tex_flag;

typedef enum e_color_flag
{
	FLOOR_FLAG = 1,
	CEIL_FLAG,
}	t_color_flag;

typedef struct s_config
{
	char		**cub;
	long long	seek;
	char		*no_tex_path;
	char		*so_tex_path;
	char		*we_tex_path;
	char		*ea_tex_path;
	t_vector	*sp_texs;
	long long	sp_num;
	int			floor_color;
	int			ceil_color;
	t_cell		**map;
	long long	height;
	long long	width;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}	t_config;

typedef struct s_sprite_path
{
	char	*path;
	int		group;
}	t_sprite_path;

// parse arg
int			parse_arg(int argc, char **argv, t_config *config);
t_error		parse_cub(t_config *config, const char *path);
t_error		parse_types(t_config *config);
t_error		parse_sprite_paths(t_config *config);
t_error		parse_map(t_config *config);
t_error		parse_colors(t_config *config, char *s, int *flag);
t_error		parse_texture_paths(t_config *config, char *s, int *flag);

// validate
t_error		validate_sprite_paths(t_config *config);
t_error		validate_sprite_id(t_config *config);
t_error		validate_texture_path(t_config *config);
t_error		validate_map(t_config *config);

// vector getter wrapper
char		*get_texture_path(t_config *config, int idx);
int			get_texture_id(t_config *config, int idx);

// utils
char		*skip_spaces(char *s);
void		skip_newline(t_config *config);
void		free_bools(bool **p);
void		free_config(t_config *config);
bool		is_texture_symbol(const char *s);
bool		is_color_symbol(const char *s);
bool		is_sprite_symbol(const char *s);
bool		is_map_symbol(const char c);
bool		has_file_ext(const char *path, char *ext);
bool		can_open(const char *path);
bool		is_direcory(const char *path);

void		sprite_pos_generator(t_cub *cub, double *x, double *y);

// config setter
void		set_player_info_in_north(t_config *config, int i, int j);
void		set_player_info_in_south(t_config *config, int i, int j);
void		set_player_info_in_east(t_config *config, int i, int j);
void		set_player_info_in_west(t_config *config, int i, int j);
t_error		set_north(t_config *config, char *s, int *flag);
t_error		set_south(t_config *config, char *s, int *flag);
t_error		set_west(t_config *config, char *s, int *flag);
t_error		set_east(t_config *config, char *s, int *flag);
t_error		new_map(t_config *config);
t_error		set_map(t_config *config);

// parse config
t_error		parse_config(t_config *config, t_cub *cub);

// cub setter
void		set_mlx_var(t_cub *cub);
void		set_player_var(t_cub *cub, t_config *config);
void		set_color_var(t_cub *cub, t_config *config);
void		set_camera_var(t_cub *cub);
void		set_time_var(t_cub *cub);
void		set_texture_var(t_cub *cub, t_config *config);
void		set_sprite_var(t_cub *cub, t_config *config);
void		set_map_var(t_cub *cub, t_config *config);
void		set_minimap_var(t_cub *cub);
t_texture	*new_texture(t_cub *cub, char *file);

#endif
