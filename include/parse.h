/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:08:51 by kkaneko           #+#    #+#             */
/*   Updated: 2022/05/23 01:29:50 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "cub3d.h"

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

int	parse_arg(int argc, char **argv, t_config *config);
t_error	load_cub(t_config *config, const char *path);
t_error	set_tex_path(t_config *config);
t_error	set_color(t_config *config);
t_error	set_sprite_paths(t_config *config);
t_error	set_map(t_config *config);

char	*skip_spaces(char *s);
bool	is_texture_symbol(const char *s);
bool	is_color_symbol(const char *s);
bool	is_sprite_symbol(const char *s);

t_error	parse_config(t_config *config, t_cub *cub);

void	sprite_position_generator(t_cub *cub, double *x, double *y);
long long	mytime(void);

void	dump_config(t_config *config);

#endif
