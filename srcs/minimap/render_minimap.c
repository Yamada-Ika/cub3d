/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:34:48 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/07 00:30:05 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx_color.h"
#include <stdio.h>

static void	draw_map_area(t_window *window);
static void	draw_map_frame(t_window *window, t_matrix *world_map);
static void	draw_map_body(t_window *window, t_player *player, t_matrix *world_map);
static void	draw_square(t_window *window,
						int center_gx, int center_gy, int color);

static void	draw_player(t_window *window, t_player *player);
static t_matrix	*translate_cordinate_to_window(t_matrix *map_pos);
static void	draw_dir_arrow(t_window *window, t_matrix *pos, t_matrix *dir);
static void	draw_line(t_window *window, t_matrix *start, t_matrix *end, int color);
static void	draw_circle(t_window *window, t_matrix *center, double r_max, int color);
static void	draw_player_dir(t_window *window, t_player *player);

static void	draw_rays(t_window *window, t_ray *rays);
static void	draw_one_ray(t_window *window, t_ray *ray);

static int	idx_is_out_of_range(int idx, size_t limit);

// tmp
void	render_minimap_tmp(t_window *window, t_matrix *world_map,
						t_player *player)
{
	draw_map_body(window, player, world_map);
	draw_map_frame(window, world_map);
	draw_player(window, player);
}

void	render_minimap(t_window *window, t_matrix *world_map,
						t_player *player)
{
	draw_map_area(window);
	draw_map_body(window, player, world_map);
	draw_map_frame(window, world_map);
	draw_player(window, player);
}

static void	draw_map_area(t_window *window)
{
	t_matrix	*center;

	center = mat_vector_col_2d(MINIMAP_POS_X, MINIMAP_POS_Y);
	draw_circle(window, center, MINIMAP_SIZE / 2, BLACK);
	mat_free(center);
}

static void	draw_map_body(t_window *window, t_player *player, t_matrix *world_map)
{
	const int	colors[3] = {WHITE, RED, BLUE};
	const int	player_x = mat_get_x(player->pos->vector);
	const int	player_y = mat_get_y(player->pos->vector);
	int			world_x;
	int			world_y;
	int			gx;
	int			gy;

	world_y = player_y - (1 / MINIMAP_ZOOM);
	while (world_y < player_y + (1 / MINIMAP_ZOOM))
	{
		world_x = player_x - (1 / MINIMAP_ZOOM);
		while (world_x < player_x + (1 / MINIMAP_ZOOM))
		{
			if (!idx_is_out_of_range(world_x, world_map->col)
				&& !idx_is_out_of_range(world_y, world_map->row))
			{
				gx = world_x - player_x + ((world_x - player_x) * 20) + MINIMAP_POS_X;
				gy = world_y - player_y + ((world_y - player_y) * 20) + MINIMAP_POS_Y;
				draw_square(window,
							gx, gy,
							colors[
							(int)world_map->values[world_y][world_x]
							]);
			}
			++world_x;
		}
		++world_y;
	}
}

static void	draw_square(t_window *window,
						int center_gx, int center_gy, int color)
{
	const int	square_size = 20;
	int			gx;
	int			gy;

	gx = center_gx - (square_size / 2);
	while (gx < center_gx + (square_size / 2))
	{
		gy = center_gy - (square_size / 2);
		while (gy < center_gy + (square_size / 2))
		{
			//printf("(%d, %d)\n", gx, gy);
			if (pow(gx - MINIMAP_POS_X, 2) + pow(gy - MINIMAP_POS_Y, 2) <= pow(MINIMAP_SIZE / 2, 2))
				my_mlx_pixel_put(window->img_back, gx, gy, color);
			++gy;
		}
		++gx;
	}
}

static void	draw_map_frame(t_window *window, t_matrix *world_map)
{
	const double	r = MINIMAP_SIZE / 2;
	double			theta;
	int				gx;
	int				gy;

	theta = 0;
	while (theta < M_PI * 2)
	{
		gx = (int)(MINIMAP_POS_X + (r * cos(theta)));
		gy = (int)(MINIMAP_POS_Y + (r * sin(theta)));
		my_mlx_pixel_put(window->img_back, gx, gy, GRAY);
		theta += MINIMAP_DELTA_THETA;
	}
}

# define START() fprintf(stderr, "start : %s %d\n", __func__, __LINE__)
# define END() fprintf(stderr, "end : %s %d\n", __func__, __LINE__)

// mapのインデックスからwindowの座標に変換
static t_matrix	*translate_cordinate_to_window(t_matrix *map_pos)
{
	t_matrix	*window_pos;
	
	window_pos = mat_vector_col_2d(mat_get_x(map_pos) * MINIMAP_SIZE,
									mat_get_y(map_pos) * MINIMAP_SIZE);
	return (window_pos);
}

static void	draw_player(t_window *window, t_player *player)
{
	t_matrix	*center;

	center = mat_vector_col_2d(MINIMAP_POS_X, MINIMAP_POS_Y);
	draw_circle(window, center, 10, GREEN);
	mat_free(center);
}

static void	draw_player_dir(t_window *window, t_player *player)
{
	const double	arrow_len = 5;
	t_matrix		*line_start;
	t_matrix		*line_end;
	t_matrix		*tmp;

	line_start = translate_cordinate_to_window(player->pos->vector);
	line_end = mat_translation_2d_new(player->dir->vector->values[0][0],
										player->dir->vector->values[1][0],
										player->pos);
	tmp = line_end;
	line_end = translate_cordinate_to_window(line_end);
	mat_free(tmp);
	draw_line(window, line_start, line_end, GREEN);
}

static void	draw_dir_arrow(t_window *window, t_matrix *pos, t_matrix *dir)
{
	//draw_line(window, pos, RED);
	draw_circle(window, pos, 3.0, RED);
}

# define TMP_DELTA_T 0.01
static void	draw_line(t_window *window, t_matrix *start,
						t_matrix *end, int color)
{
	double	t;
	double	plot_x;
	double	plot_y;

	t = 0;
	while (t < 1)
	{
		plot_x = ((t * end->values[0][0]) + ((1 - t) * start->values[0][0]));
		plot_y = ((t * end->values[1][0]) + ((1 - t) * start->values[1][0]));
		my_mlx_pixel_put(window->img_back, plot_x, plot_y, color);
		t += MINIMAP_DELTA_T;
	}
}

static void	draw_circle(t_window *window, t_matrix *center, double r_max, int color)
{
	double	r;
	double	theta;
	double	plot_x;
	double	plot_y;

	r = 0;
	while (r <= r_max)
	{
		theta = 0;
		while (theta < M_PI * 2)
		{
			plot_x = mat_get_x(center) + (r * cos(theta));
			plot_y = mat_get_y(center) + (r * sin(theta));
			my_mlx_pixel_put(window->img_back, plot_x, plot_y, color);
			theta += MINIMAP_DELTA_THETA;
		}
		r += MINIMAP_DELTA_R;
	}
}

void	draw_ray_on_minimap(t_window *window, t_ray *ray)
{
	const double	len_ray = ray->v_distance * 1;
	const double	delta_t = 0.01;
	double			plot_x;
	double			plot_y;
	double			t;

	t = 0;
	while (t < len_ray)
	{
		plot_x = (mat_get_x(ray->from) + (t * mat_get_x(ray->dir->vector))) * MINIMAP_SIZE;
		plot_y = (mat_get_y(ray->from) + (t * mat_get_y(ray->dir->vector))) * MINIMAP_SIZE;
		if (ray->side == X_SIDE)
			my_mlx_pixel_put(window->img_back, plot_x, plot_y, YELLOW/2);
		else
			my_mlx_pixel_put(window->img_back, plot_x, plot_y, YELLOW);
		t += delta_t;
	}
	// 衝突した座標をプロット
	plot_x = ray->collide_at_x * MINIMAP_SIZE;
	plot_y = ray->collide_at_y * MINIMAP_SIZE;
	my_mlx_pixel_put(window->img_back, plot_x, plot_y, GREEN);
}

static int	idx_is_out_of_range(int idx, size_t limit)
{
	if (idx < 0 || idx >= (int)limit)
		return (1);
	else
		return (0);
}

static int	can_draw_pixel(int gx, int gy, t_matrix *world_map)
{
	if (pow(gx - MINIMAP_POS_X, 2) + pow(gy - MINIMAP_POS_Y, 2)
		> pow(MINIMAP_SIZE / 2, 2))
		return (1);
	else if (gx >= world_map->col || gy >= world_map->row)
		return (1);
	else
		return (0);
}
