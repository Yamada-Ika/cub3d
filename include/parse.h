/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:08:51 by kkaneko           #+#    #+#             */
/*   Updated: 2022/05/12 22:06:34 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "cub3d.h"

// vector data structure
typedef struct s_vector
{
	char	**data;
	size_t	cap; // メモリ領域の長さ
	size_t	len; // データが詰まってるサイズ
}	t_vector;

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
	int		**map;
	long long	height;
	long long	width;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_config;

typedef enum e_error
{
	NO_ERR,
	INVALID_ARG_NUM_ERR,
	INVALID_CUB_FILE,
	CUB_FILE_ERR,
	MEM_ERR,
	TEX_FILE_ERR,
	INVALID_RGB,
	NON_CLOSED_MAP,
	NON_PLAYER,
}	t_error;

// ------------------- init cub -------------------
void	sprite_position_generator(t_cub *cub, double *x, double *y);
long long	mytime(void);

#endif
