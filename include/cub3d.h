/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:08:51 by kkaneko           #+#    #+#             */
/*   Updated: 2022/06/08 17:13:10 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/time.h>

# include "libft.h"
# include "mlx.h"
# include "mlx_window.h"
# include "vector.h"

# define USAGE "usage: ./cub3d <a map in format *.cub>\n"
# define MOVE_STEP 0.5
# define SP_MOVE_STEP 0.01
# define ROT_STEP 0.05

typedef enum e_jump_state
{
	ON_GROUND,
	JUMPING,
	GETTING_OFF,
}	t_jump_state;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	t_jump_state	jump_state;
	double			velocity_z;
	double			elevation;
}	t_player;

typedef struct s_texture
{
	int		width;
	int		height;
	t_img	*img;
}	t_texture;

typedef struct s_sprite
{
	t_vector	*textures;
	double		x;
	double		y;
	double		dist_from_player;
	int			len;
}	t_sprite;

typedef struct s_sprite_info
{
	t_sprite	*sprites;
	int			num;
	double		*buf_perp;
}	t_sprite_info;

typedef enum e_cell_kind
{
	NONE,
	WALL,
	DOOR,
}	t_cell_kind;

typedef enum e_door_state_kind
{
	CLOSE,
	CLOSING,
	OPEN,
	OPENING,
}	t_door_state_kind;

typedef enum e_door_side_kind
{
	TRANSVERSE,
	LONGITUDINAL,
}	t_door_side_kind;

typedef struct s_cell
{
	t_cell_kind			kind;
	t_door_state_kind	door_state;
	t_door_side_kind	side;
	double				timer;
}	t_cell;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	t_cell			**map;
	int				width;
	int				heigth;
	unsigned int	floor;
	unsigned int	ceil;
	t_texture		*north;
	t_texture		*south;
	t_texture		*west;
	t_texture		*east;
	t_vector		*door_points;
}	t_map;

typedef struct s_minimap_info
{
	unsigned int	**buf;
	int				width;
	int				height;
}	t_minimap_info;

typedef struct s_camera
{
	double	pitch;
	double	vertical_pos;
}	t_camera;

typedef struct s_cub
{
	t_window		*window;
	t_player		*player;
	t_map			*map;
	t_sprite_info	*sprite;
	t_minimap_info	*minimap;
	t_camera		*camera;
	long long		timestamp;
}	t_cub;

typedef enum e_error
{
	NO_ERR,
	PARSE_CUB_EXTENSION_ERR,
	PARSE_CUB_CANT_OPEN_ERR,
	PARSE_CUB_IS_DIRECTORY_ERR,
	INVALID_ARG_NUM_ERR,
	CUB_FILE_READ_ERR,
	UNKNOWN_SYMBOL,
	DUPLICATE_NORTH_TEX_ERR,
	DUPLICATE_SOUTH_TEX_ERR,
	DUPLICATE_WEST_TEX_ERR,
	DUPLICATE_EAST_TEX_ERR,
	NOT_ENOUGH_WALL_TEX_ERR,
	DUPLICATE_FLOOR_COLOR_ERR,
	DUPLICATE_CEIL_COLOR_ERR,
	INVALID_COLOR_VAL_ERR,
	INVALID_SPRITE_ID_ERR,
	UNKNOWN_MAP_SYMBOL,
	COLOR_UNKNOWN_SYMBOL_ERR,
	VALIDATE_NORTH_TEX_NOT_XPM_ERR,
	VALIDATE_SOUTH_TEX_NOT_XPM_ERR,
	VALIDATE_WEST_TEX_NOT_XPM_ERR,
	VALIDATE_EAST_TEX_NOT_XPM_ERR,
	VALIDATE_NORTH_TEX_CANT_OPEN_ERR,
	VALIDATE_SOUTH_TEX_CANT_OPEN_ERR,
	VALIDATE_WEST_TEX_CANT_OPEN_ERR,
	VALIDATE_EAST_TEX_CANT_OPEN_ERR,
	VALIDATE_NORTH_TEX_IS_DIRECTORY_ERR,
	VALIDATE_SOUTH_TEX_IS_DIRECTORY_ERR,
	VALIDATE_WEST_TEX_IS_DIRECTORY_ERR,
	VALIDATE_EAST_TEX_IS_DIRECTORY_ERR,
	VALIDATE_MAP_ISNOT_RECTANGLE_ERR,
	VALIDATE_MAP_HAS_INVALID_CHAR_ERR,
	VALIDATE_MAP_ISNOT_CLOSED_ERR,
	VALIDATE_SPRITE_TEX_NOT_XPM_ERR,
	VALIDATE_SPRITE_TEX_CANT_OPEN_ERR,
	VALIDATE_SPRITE_TEX_IS_DIRECTORY_ERR,
	VALIDATE_INVALID_SPRITE_ID_ERR,
	CUB_ELEMENT_NOT_ENOUGH_ERR,
	INVALID_CUB_FILE,
	CUB_FILE_ERR,
	MEM_ERR,
	TEX_FILE_ERR,
	INVALID_RGB,
	NON_CLOSED_MAP,
	NON_PLAYER,
}	t_error;

int			render(t_cub *cub);
long long	gettimestamp(void);

#endif
