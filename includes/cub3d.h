/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:29:56 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/04 21:30:32 by kkaneko          ###   ########.fr       */
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

# define RAY_NUM 800
# define H 500
# define WIN_TITLE "cub3d"
# define FOV M_PI_2
# define MOVE_STEP 0.1
# define PERSPECT_ROT_RATE 0.1
# define BLOCK_SIZE 256
# define DELTA_T 0.03
# define LEN_RAY 100
# define IMG_PLANE_LEN 2
# define MINIMAP_SIZE 150
# define MINIMAP_ZOOM 1
# define MINIMAP_DELTA_T 0.01
# define MINIMAP_DELTA_R 0.01
# define MINIMAP_DELTA_THETA 0.01

typedef struct s_map
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color;
	int		ceilling_color;
	t_matrix	*map;
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
	int	side;
}	t_ray;

typedef struct s_game
{
	t_window	*window;
	t_map		*map;
	t_player	*player;
}	t_game;

typedef enum e_state
{
	FAIL,
	SUCCESS,
	X_SIDE,
	Y_SIDE,
}	t_state;

t_map	*parse_map(const char *map_file);
void	set_hooks(t_game *game);
void	render_minimap(t_window *window, t_matrix *world_map,
						t_player *player, t_ray *rays);
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
void	move_straight(t_player *player);
void	move_left(t_player *player);
void	move_back(t_player *player);
void	move_right(t_player *player);
void	turn_right(t_player *player);
void	turn_left(t_player *player);

/* minimap */
void	draw_ray_on_minimap(t_window *window, t_ray *ray);

/* utils */
void	exit_with_error(const char *str, int status);

#endif
