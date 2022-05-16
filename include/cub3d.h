/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:08:51 by kkaneko           #+#    #+#             */
/*   Updated: 2022/05/16 18:29:53 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

#include "libft.h"
#include "mlx.h"
#include "mlx_window.h"
#include "vector.h"

#define mapWidth 24
#define mapHeight 24
#define w 800
#define h 1000
#define RGB_Red 0xff0000
#define RGB_Green 0x00ff00
#define RGB_Blue 0x0000ff
#define RGB_White 0xffffff
#define RGB_Black 0x000000
#define RGB_Yellow 0xffff00
#define MOVE_STEP 0.5
#define SP_MOVE_STEP 0.01
#define ROT_STEP 0.05

typedef struct s_player {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_texture
{
	int		width;
	int		height;
	t_img	*img;
}	t_texture;

// TODO tex -> vectorにしてアニメーションに対応
typedef struct s_sprite
{
	t_vector	*textures;
	double	x;
	double	y;
	double	dist_from_player;
	int		len;
}	t_sprite;

typedef struct s_sprite_info
{
	t_sprite	*sprites;
	int	num;
	double		*buf_perp;
}	t_sprite_info;

typedef struct s_map {
	int			**map;
	int 		width;
	int 		heigth;
	unsigned int	floor;
	unsigned int	ceil;
	t_texture	*north;
	t_texture	*south;
	t_texture	*west;
	t_texture	*east;
}	t_map;

typedef struct s_minimap_info
{
	unsigned int	**buf;
	int	width;
	int	height;
}	t_minimap_info;

typedef struct timeval	t_time;

typedef struct s_camera
{
	double	pitch;
	double	vertical_pos;
}	t_camera;

typedef struct s_cub {
	t_window		*window;
	t_player		*player;
	t_map			*map;
	t_sprite_info	*sprite;
	t_minimap_info	*minimap;
	t_camera		*camera;
	t_time			timestamp;
}	t_cub;

void	render(t_cub *cub);

// mlx wrapper
void	put_pixel(t_cub *cub, int x, int y, unsigned int color);
void	put_image(t_cub *cub);

#endif
