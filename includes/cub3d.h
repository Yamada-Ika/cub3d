/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:29:56 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/07 01:54:50 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "libmat.h"
# include "mlx.h"
# include "mlx_window.h"
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <float.h>

# define RAY_NUM 1200
# define H 700
# define WIN_TITLE "cub3d"
# define FOV M_PI_2
# define MOVE_STEP 0.1
# define PERSPECT_ROT_RATE 0.1
# define BLOCK_SIZE 256
# define DELTA_T 0.03
# define LEN_RAY 100
# define IMG_PLANE_LEN 2
# define MINIMAP_SIZE 150
# define MINIMAP_POS_X 80
# define MINIMAP_POS_Y 80
# define MINIMAP_ZOOM 0.1
# define MINIMAP_DELTA_T 0.01
# define MINIMAP_DELTA_R 0.05
# define MINIMAP_DELTA_THETA 0.01
# define MOUSE_SENSITIVITY 0.2
# define MOUSE_ROT_INTERVAL 20

# define DBG() fprintf(stderr, "%s %d\n", __func__, __LINE__)

typedef enum e_error
{
	NO_ERR,
	INVALID_ARG_NUM,
	INVALID_CUB_FILE,
	CUB_FILE_ERR,
	MEM_ERR,
	TEX_FILE_ERR,
	INVALID_RGB,
	NON_CLOSED_MAP,
	NON_PLAYER,
}	t_error;

typedef enum e_state
{
	FAIL,
	SUCCESS,
	X_SIDE,
	Y_SIDE,
}	t_state;

typedef enum e_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}	t_side;

typedef struct s_config
{
	char	*no_tex_path;
	char	*so_tex_path;
	char	*we_tex_path;
	char	*ea_tex_path;
	int		floor_color;
	int		ceilling_color;
	char	**map;
	size_t	map_col_size;
	size_t	map_row_size;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
}	t_config;

typedef struct s_texture
{
	int	width;
	int	height;
	t_img	*img;
}	t_texture;

typedef struct s_map
{
	t_texture		*no;
	t_texture		*so;
	t_texture		*we;
	t_texture		*ea;
	unsigned int	floor_color;
	unsigned int	ceilling_color;
	t_matrix		*map;
}	t_map;

typedef struct s_player
{
	t_affine	*pos;
	t_affine	*dir;
}	t_player;

typedef struct s_ray
{
	size_t		index;
	t_affine	*dir;
	t_vector	*from;
	double		angle;
	double		v_distance;
	int			color;
	t_vector	*collision;
	double		collide_at_x;
	double		collide_at_y;
	int	side;
}	t_ray;

typedef struct s_game
{
	t_window	*window;
	t_map		*map;
	t_player	*player;
}	t_game;

// t_map	*parse_map(const char *map_file);
void	set_hooks(t_game *game);
void	render_minimap(t_window *window, t_matrix *world_map,
						t_player *player);
void	render_minimap_tmp(t_window *window, t_matrix *world_map,
						t_player *player); // tmp
void	render(t_game *game);

/* get_3d_image */
void	get_3d_image(t_game *game);

/* spawn */
t_player	*spawn_player(double pos_x, double pos_y,
							double dir_x, double dir_y);

/* hooks */
void	clear_window(t_window *window);
int		handle_movement(int keycode, t_game *game);
int		handle_perspective(int keycode, t_game *game);
// void	move_straight(t_player *player);
// void	move_left(t_player *player);
// void	move_back(t_player *player);
// void	move_right(t_player *player);
void	turn_right(t_player *player, double rot_rate);
void	turn_left(t_player *player, double rot_rate);

/* minimap */
void	draw_ray_on_minimap(t_window *window, t_ray *ray);

/* utils */
void	exit_with_error(const char *str, int status);

#endif
