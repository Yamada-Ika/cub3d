/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:34:48 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 03:15:40 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx_color.h"
#include <stdio.h>

static void	draw_map_body(t_window *window, t_matrix *world_map);
static void	draw_square(t_window *window,
						size_t world_x, size_t world_y, int color);

static void	draw_player(t_window *window, t_player *player);
static t_matrix	*translate_cordinate_to_window(t_matrix *map_pos);
static void	draw_dir_arrow(t_window *window, t_matrix *pos, t_matrix *dir);
static void	draw_line(t_window *window, t_matrix *pos, int color);
//static void	draw_circle(t_window *window, double x, double y, double r, int color);
static void	draw_circle(t_window *window, t_matrix *center, double r_max, int color);

static void	draw_rays(t_window *window, t_ray *rays);
static void	draw_one_ray(t_window *window, t_ray *ray);

static int	idx_is_out_of_range(int idx, size_t limit);

// tmp
void	render_minimap_tmp(t_window *window, t_matrix *world_map,
						t_player *player)
{
	draw_map_body(window, world_map);
	draw_player(window, player);
}

void	render_minimap(t_window *window, t_matrix *world_map,
						t_player *player, t_ray *rays)
{
	draw_map_body(window, world_map);
	draw_player(window, player);
	draw_rays(window, rays);
}

static void	draw_map_body(t_window *window, t_matrix *world_map)
{
	const size_t	row = world_map->row;
	const size_t	col = world_map->col;
	const int		colors[3] = {WHITE, RED, BLUE};
	size_t	i;
	size_t	j;

	i = 0;
	while (i < row)
	{
		j = 0;
		while (j < col)
		{
			draw_square(window, j, i, colors[(int)(world_map->values[i][j])]);
			++j;
		}
		++i;
	}
}

static void	draw_square(t_window *window,
						size_t world_x, size_t world_y, int color)
{
	const int	start_x = (int)world_x * MINIMAP_SIZE;
	const int	start_y = (int)world_y * MINIMAP_SIZE;
	size_t		i;
	size_t		j;

	i = 0;
	while (i < MINIMAP_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SIZE)
		{
			if (!idx_is_out_of_range(start_x + i, WIN_W)
				&& !idx_is_out_of_range(start_y + j, WIN_H))
			{
				if (i == 0 || i == MINIMAP_SIZE - 1 || j == 0 || j == MINIMAP_SIZE - 1)
					my_mlx_pixel_put(window->img, (int)(start_x + i), (int)(start_y + j), BLACK);
				else
					my_mlx_pixel_put(window->img, (int)(start_x + i), (int)(start_y + j), color);
			}
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
	
	window_pos = mat_vector_col_2d(map_pos->values[0][0] * MINIMAP_SIZE + MINIMAP_SIZE/2,
									map_pos->values[1][0] * MINIMAP_SIZE + MINIMAP_SIZE/2);
	return (window_pos);
}

static void	draw_player(t_window *window, t_player *player)
{
	t_matrix	*win_pos;

	win_pos = translate_cordinate_to_window(player->pos->vector);
	draw_circle(window, win_pos, 10, GREEN);
	mat_free(win_pos);
}

static void	draw_dir_arrow(t_window *window, t_matrix *pos, t_matrix *dir)
{
	draw_line(window, pos, RED);
	draw_circle(window, pos, 3.0, RED);
}

# define TMP_DELTA_T 0.01
static void	draw_line(t_window *window, t_matrix *pos, int color)
{
	t_matrix	*tmp;
	double		tmp_x;
	double		tmp_y;

	double t = TMP_DELTA_T;
	while (42)
	{
		tmp = mat_mul_scalar_new(t, pos);
		tmp_x = tmp->values[0][0];
		tmp_y = tmp->values[1][0];
		if (
			t > 0.10
		)
		{
			return ;
		}
		my_mlx_pixel_put(window->img, tmp_x, tmp_y, color);
		mat_free(tmp);
		t += TMP_DELTA_T;
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
			if (!idx_is_out_of_range(plot_x, WIN_W)
				&& !idx_is_out_of_range(plot_y, WIN_H))
				my_mlx_pixel_put(window->img, plot_x, plot_y, color);
			theta += MINIMAP_DELTA_THETA;
		}
		r += MINIMAP_DELTA_R;
	}
}

static void	draw_rays(t_window *window, t_ray *rays)
{
	size_t			ray_i;

	ray_i = 0;
	while (ray_i < RAY_NUM)
	{
		draw_one_ray(window, &(rays[ray_i]));
		++ray_i;
	}
}

static void	draw_one_ray(t_window *window, t_ray *ray)
{
	const double	len_ray = 3;
	const double	delta_t = 0.01;
	double			plot_x;
	double			plot_y;
	double			t;

	t = 0;
	while (t < len_ray)
	{
		plot_x = (ray->from->values[0][0] + (t * ray->dir->vector->values[0][0])) * MINIMAP_SIZE + MINIMAP_SIZE/2;
		plot_y = (ray->from->values[1][0] + (t * ray->dir->vector->values[1][0])) * MINIMAP_SIZE + MINIMAP_SIZE/2;
		if (!idx_is_out_of_range(plot_x, WIN_W)
			&& !idx_is_out_of_range(plot_y, WIN_H))
			my_mlx_pixel_put(window->img, plot_x, plot_y, YELLOW);
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

