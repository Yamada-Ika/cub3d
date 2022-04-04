/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:19:50 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/31 18:443:44 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include "includes/mlx_window.h"
#include "includes/mlx_color.h"
#include <stdlib.h>

static void	**allocate_double_pointer(size_t row_byte, size_t col_byte);
static double	abs_double(double a);
static void	place_block(t_matrix *world_map, size_t place_i, size_t place_j);
static t_matrix	*gen_world_map();
static t_player	*gen_player(double pos_x, double pos_y,
							double dir_x, double dir_y);
static void	ft_raycast(t_ray *rays, t_matrix *world_map);
static void	render_3d(t_window *window, t_ray *rays);
static void	raycast_test(t_window *window);
static t_ray	*gen_rays(t_player *player);
static int	has_collide(t_ray *ray, double t, t_matrix *world_map);
static void	draw_line_v(t_window *window, t_matrix *center,
						size_t length, int color);
static int	idx_is_out_of_range(int idx, size_t limit);
static double	get_rotation_angle(double theta);

static t_ray	*new_ray(void)
{
	t_ray	*new;

	new = (t_ray *)ft_calloc(1, sizeof(t_ray));
	new->dir = mat_affine_new(2);
	return (new);
}

/* 関数分けても良いかも
set_ray_index
set_ray_angle
set_ray_dir
set_ray_start_pos
*/
static void	set_ray(t_ray *this, size_t index, t_matrix *from, t_matrix *dir)
{
	const double	delta_theta = FOV / RAY_NUM;

	this->angle = get_rotation_angle(delta_theta * (double)index);
	this->dir->vector = mat_dup(dir);
	mat_rotation_2d(this->angle, this->dir);
	this->from = mat_dup(from);// set_cast_pos, set_radiate_pos, set_start_point
	this->index = index;
}

/*
has_collideの粒度がデカすぎるかも
*/
static void	cast_ray(t_ray *this, t_map *map)
{
	double	t;

	t = DELTA_T;
	while (42)
	{
		if (has_collide(this, t, map->map) != 0)
			break ;
		t += DELTA_T;
	}
}

// draw_3d_imageとか？
void	get_3d_image(t_game *game)
{
	// t_matrix	*world_map;
	t_player	*player;
	t_ray		*ray;
	size_t		ray_index;

	// world_map = game->map->map;
	player = game->player;

	// printf("ply pos:(%f, %f)\n",
	// 		player->pos->vector->values[0][0],
	// 		player->pos->vector->values[1][0]);
	ray = new_ray(); // 光線用の変数を作成
	ray_index = 0;
	while (ray_index < RAY_NUM) // 光線の数だけループ回す
	{
		set_ray(ray, ray_index,
				game->player->pos->vector,
				game->player->dir->vector); // 光線の向きとかセット
		cast_ray(ray, game->map); // 光線を伸ばして衝突判定
		render_3d(game->window, ray); // windowに描画
		draw_ray_on_minimap(game->window, ray); //minimapに描画
		ray_index++;
	}
	//render_minimap_tmp(game->window, game->map->map, player); // ミニマップを作成
}

static double	get_rotation_angle(double theta)
{
	return ((FOV / 2.0) - theta);
}

static int	has_collide(t_ray *ray, double t, t_matrix *world_map)
{
	int			res;
	t_vector	*collide;
	t_vector	*tmp;
	double	collide_x;
	double	collide_y;

	//tmp = mat_mul_scalar_new(t, ray->dir->vector);
	tmp = mat_zoom_2d_new(t, t, ray->dir);
	collide = mat_add_new(ray->from, tmp);
	collide_x = collide->values[0][0]; //光の先端の座標
	collide_y = collide->values[1][0];
	//printf("collide_x:%f, y:%f\n", collide_x, collide_y);

	double dist_next_x_side;
	double dist_next_y_side;
	if (mat_get_x(ray->dir->vector) > 0) // 光が+xの方向に進んでいる
		dist_next_x_side = collide_x - ((int)collide_x - 1);
	else // 光が-xの方向に進んでいる
		dist_next_x_side = ((int)collide_x + 1) - collide_x;
	if (mat_get_y(ray->dir->vector) > 0) // 光が+yの方向に進んでいる
		dist_next_y_side = collide_y - ((int)collide_y - 1);
	else // 光が-yの方向に進んでいる
  		dist_next_y_side = ((int)collide_y + 1) - collide_y;

	int side;
	if (dist_next_x_side < dist_next_y_side)
		side = X_SIDE;
	else
		side = Y_SIDE;

	if (idx_is_out_of_range((int)collide_x, world_map->col)
		|| idx_is_out_of_range((int)collide_y, world_map->row))
		res = -1;
	else if (world_map->values[(int)collide_y][(int)collide_x] > 0)
	{
		// // debug
		//printf("collide_x        %f collide_y %f\n", collide_x, collide_y);
		//printf("dist_next_x_side %f dist_next_y_side %f\n", dist_next_x_side, dist_next_y_side);

		mat_mul_scalar(-1, ray->from);
		collide->values[0][0] += ray->from->values[0][0]; // vectorをたす
		collide->values[1][0] += ray->from->values[1][0];

		ray->v_distance = abs_double((mat_distance_2d(collide) * cos(ray->angle))
							- (IMG_PLANE_LEN / (2 * tan(FOV / 2.0))));
		if (world_map->values[(int)collide_y][(int)collide_x] == 2)
			ray->color = BLUE;
		else
			ray->color = RED;

		// xサイドを暗くする
		if (side == X_SIDE) 
		{
			ray->color = create_trgb(get_t(ray->color),
									get_r(ray->color) / 2,
									get_g(ray->color) / 2,
									get_b(ray->color) / 2);
			//printf("side color %x\n", ray->color);
		}
		res = 1;
	}
	else
		res = 0;
	mat_free(collide);
	mat_free(tmp);
	return (res);
}

static void	render_3d(t_window *window, t_ray *ray)
{
	size_t		line_length;
	int			line_color;
	t_matrix	*center_of_line;

	center_of_line = mat_vector_col_2d(RAY_NUM - ray->index - 1, WIN_H / 2);
	line_length = (size_t)(1000 / (1.0 + ray->v_distance));
	line_color = ray->color;
	//printf("center:(%d, %d) length:%zu\n", (int)center_of_line->values[0][0], (int)center_of_line->values[0][1], line_length);
	draw_line_v(window, center_of_line, line_length, line_color);
	mat_free(center_of_line);
}

static void	draw_line_v(t_window *window, t_matrix *center,
						size_t length, int color)
{
	const int	start_x = center->values[0][0];
	const int	start_y = center->values[1][0];
	size_t		i;

	i = 0;
	while (i < length / 2)
	{
		if (!idx_is_out_of_range(start_y + i, WIN_H))
			my_mlx_pixel_put(window->img_back, start_x, start_y + (int)i, color);
		if (!idx_is_out_of_range(start_y - i, WIN_H))
			my_mlx_pixel_put(window->img_back, start_x, start_y - (int)i, color);
		++i;
	}
}

/* utils */

static void	**allocate_double_pointer(size_t row_byte, size_t col_byte)
{
	void			**res;
	unsigned char	**uc_res;
	size_t			i;

	res = ft_calloc(row_byte, sizeof(void *));
	uc_res = (unsigned char **)res;
	i = 0;
	while (i < row_byte)
	{
		uc_res[i] = ft_calloc(col_byte, 1);
		++i;
	}
	return (res);
}

static double	abs_double(double a)
{
	return (sqrt(pow(a, 2)));
}

static int	idx_is_out_of_range(int idx, size_t limit)
{
	if (idx < 0 || (size_t)idx >= limit)
		return (1);
	else
		return (0);
}
