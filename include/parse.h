/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:08:51 by kkaneko           #+#    #+#             */
/*   Updated: 2022/05/23 18:58:39 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "cub3d.h"

# define A 48271
# define B 0
# define M INT_MAX

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
	char	**cub;
	long long	seek;
	char	*no_tex_path;
	char	*so_tex_path;
	char	*we_tex_path;
	char	*ea_tex_path;
	t_vector	*sp_texs;
	long long sp_num;
	int		floor_color;
	int		ceil_color;
	t_cell	**map;
	long long	height;
	long long	width;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_config;

typedef struct s_sprite_path
{
	char	*path;
	int		group;
}	t_sprite_path;

// parse arg
int	parse_arg(int argc, char **argv, t_config *config);
t_error	load_cub(t_config *config, const char *path);
t_error	set_tex_path(t_config *config);
t_error	set_color(t_config *config);
t_error	set_sprite_paths(t_config *config);
t_error	set_map(t_config *config);

// utils
char	*skip_spaces(char *s);
void	skip_newline(t_config *config);
bool	is_texture_symbol(const char *s);
bool	is_color_symbol(const char *s);
bool	is_sprite_symbol(const char *s);

// parse config
t_error	parse_config(t_config *config, t_cub *cub);
void	set_texture_var(t_cub *cub, t_config *config);
void	set_sprite_var(t_cub *cub, t_config *config);
void	set_map_var(t_cub *cub, t_config *config);
void	set_minimap_var(t_cub *cub);
t_texture	*new_texture(t_cub *cub, char *file);

void	sprite_pos_generator(t_cub *cub, double *x, double *y);

void	dump_config(t_config *config);

// config setter
void	set_player_info_in_north(t_config *config, int i, int j);
void	set_player_info_in_south(t_config *config, int i, int j);
void	set_player_info_in_east(t_config *config, int i, int j);
void	set_player_info_in_west(t_config *config, int i, int j);
t_error	set_north(t_config *config, char *s, int *flag);
t_error	set_south(t_config *config, char *s, int *flag);
t_error	set_west(t_config *config, char *s, int *flag);
t_error	set_east(t_config *config, char *s, int *flag);
t_error	new_map(t_config *config);

// cub setter
void	set_mlx_var(t_cub *cub);
void	set_player_var(t_cub *cub, t_config *config);
void	set_color_var(t_cub *cub, t_config *config);
void	set_camera_var(t_cub *cub);
void	set_time_var(t_cub *cub);

#endif
