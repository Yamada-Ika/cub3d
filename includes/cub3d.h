/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:29:56 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/31 22:41:09 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libmat.h"
# include "mlx.h"
# include "mlx_window.h"
# include <stdio.h>
# include <math.h>

# define RAY_NUM 1366
# define WIN_W 1366
# define WIN_H 768
# define MINIMAP_SIZE 40
# define WIN_TITLE "cub3d"
# define FOV M_PI_2
# define MOVE_STEP 0.1
# define BLOCK_SIZE 256
# define DELTA_T 0.03
# define LEN_RAY 100
# define IMG_PLANE_LEN 2

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
	t_matrix	*pos;
	t_matrix	*dir;
}	t_player;

typedef struct s_ray
{
	t_matrix	*dir;
	double		phi;
	double		v_distance;
	int			color;
	t_player	*player;
}	t_ray;

typedef struct s_game
{
	t_window	*window;
	t_map		*map;
	t_player	*player;
}	t_game;


t_map	*parse_map(const char *map_file);
void	set_hooks(t_game *game);
void	render_minimap(t_window *window, t_matrix *world_map,
						t_player *player, t_ray *rays);
void	render(t_game *game);
t_img	*init_img(t_window *window);

/* get_3d_image */
void	get_3d_image(t_game *game);

/* spawn */
t_player	*spawn_player(double pos_x, double pos_y,
							double dir_x, double dir_y);

/* hooks */
void	clear_window(t_window *window);

/* utils */
void	exit_with_error(const char *str, int status);

#endif
