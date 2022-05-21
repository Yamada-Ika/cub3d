/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:08:51 by kkaneko           #+#    #+#             */
/*   Updated: 2022/05/21 16:08:56 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "cub3d.h"

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

// ------------------- init cub -------------------
void	sprite_position_generator(t_cub *cub, double *x, double *y);
long long	mytime(void);

// dump
void	dump_config(t_config *config);

#endif
