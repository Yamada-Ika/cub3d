/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:34:48 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/05 00:43:35 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx_color.h"
#include <stdio.h>

static void	draw_map_frame(t_window *window, t_matrix *world_map);
static void	draw_map_body(t_window *window, t_player *player, t_matrix *world_map);
static void	draw_square(t_window *window,
						size_t world_x, size_t world_y, int color);

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
						t_player *player, t_ray *ray)
{
	draw_map_body(window, player, world_map);
	draw_map_frame(window, world_map);
	draw_player(window, player);
}

static void	draw_map_frame(t_window *window, t_matrix *world_map)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			if (y == 0 || y == MINIMAP_SIZE - 1
				|| x == 0 || x == MINIMAP_SIZE - 1)
				my_mlx_pixel_put(window->img_back, x, y, GRAY);
			++x;
		}
		++y;
	}
}

static void	draw_map_body(t_window *window, t_player *player, t_matrix *world_map)
{
	const int	colors[3] = {WHITE, RED, BLUE};
	int 		minimap_x;
	int			minimap_y;
	int			plot_x;
	int			plot_y;

	minimap_y = 0;
	while (minimap_y < MINIMAP_SIZE)
	{
		minimap_x = 0;
		while (minimap_x < MINIMAP_SIZE)
		{
			plot_x = (mat_get_x(player->pos->vector) * WIN_W) - (MINIMAP_SIZE / 2) + minimap_x;
			plot_y = (mat_get_y(player->pos->vector) * WIN_H) - (MINIMAP_SIZE / 2) + minimap_y;
			draw_square(window,
						plot_x, plot_y,
						colors[(int)(world_map->values[plot_y][plot_x])]);
			++minimap_x;
		}
		++minimap_y;
	}
}

static void	draw_square(t_window *window,
						size_t world_x, size_t world_y, int color)
{
	const int	square_size = MINIMAP_ZOOM * MINIMAP_SIZE / 10;
	const int	start_x = (int)world_x * MINIMAP_SIZE;
	const int	start_y = (int)world_y * MINIMAP_SIZE;
	size_t		i;
	size_t		j;

	i = 0;
	while (i < square_size)
	{
		j = 0;
		while (j < square_size);
		{
			my_mlx_pixel_put(window->img_back,
							(int)(start_x + i), (int)(start_y + j), color);
			++j;
		}
		++i;
	}
}

# define START() fprintf(stderr, "start : %s %d\n", __func__, __LINE__)
# define END() fprintf(stderr, "end : %s %d\n", __func__, __LINE__)

// mapのインデックスからwindowの座標に変換
static t_matrix	*translate_cordinate_to_window(t_matrix *map_pos)
{
	t_matrix	*window_pos;
	
	window_pos = mat_vector_col_2d(map_pos->values[0][0] * MINIMAP_SIZE,
									map_pos->values[1][0] * MINIMAP_SIZE);
	return (window_pos);
}

static void	draw_player(t_window *window, t_player *player)
{
	t_matrix	*win_pos;

	win_pos = translate_cordinate_to_window(player->pos->vector);
	draw_circle(window, win_pos, 10, GREEN);
	draw_player_dir(window, player);
	mat_free(win_pos);
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
			plot_x = center->values[0][0] + (r * cos(theta));
			plot_y = center->values[1][0] + (r * sin(theta));
			my_mlx_pixel_put(window->img_back, plot_x, plot_y, color);
			theta += MINIMAP_DELTA_THETA;
		}
		r += MINIMAP_DELTA_R;
	}
}

void	draw_ray_on_minimap(t_window *window, t_ray *ray)
{
	const double	len_ray = 5;
	const double	delta_t = 0.01;
	double			plot_x;
	double			plot_y;
	double			t;

	t = 0;
	while (t < len_ray)
	{
		plot_x = (mat_get_x(ray->from) + (t * mat_get_x(ray->dir->vector))) * MINIMAP_SIZE;
		plot_y = (mat_get_y(ray->from) + (t * mat_get_y(ray->dir->vector))) * MINIMAP_SIZE;
		if (!idx_is_out_of_range(plot_x, WIN_W)
			&& !idx_is_out_of_range(plot_y, WIN_H))
		{
			if (ray->side == X_SIDE)
				my_mlx_pixel_put(window->img_back, plot_x, plot_y, YELLOW/2);
			else
				my_mlx_pixel_put(window->img_back, plot_x, plot_y, YELLOW);
		}
		t += delta_t;
	}
}

static int	idx_is_out_of_range(int idx, size_t limit)
{
	if (idx < 0 || idx > limit)
		return (1);
	else
		return (0);
}

