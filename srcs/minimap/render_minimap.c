/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:34:48 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/01 18:30:51 by kkaneko          ###   ########.fr       */
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
	//t_matrix	*window_pos = mat_new(3, 1);

	t_matrix	*window_pos;
	
	window_pos = mat_vector_col_2d(map_pos->values[0][0] * MINIMAP_SIZE + MINIMAP_SIZE/2,
									map_pos->values[1][0] * MINIMAP_SIZE + MINIMAP_SIZE/2);
	/*
	START();
	window_pos->values[0][0] = map_pos->values[0][0] * MINIMAP_SIZE;
	window_pos->values[1][0] = map_pos->values[1][0] * MINIMAP_SIZE;
	END();
	*/
	return (window_pos);
}

static void	draw_player(t_window *window, t_player *player)
{
	t_matrix	*win_pos;
	double		win_x;
	double		win_y;

	START();
	// draw_square(window, player->pos[0][0], player->pos[1][0], BLACK);
	win_pos = translate_cordinate_to_window(player->pos);
	win_x = win_pos->values[0][0];
	win_y = win_pos->values[1][0];
	fprintf(stderr, "win_x %f, win_y %f\n", win_x, win_y);
	//draw_circle(window, win_x, win_y, 10, GREEN);
	draw_circle(window, win_pos, 10, GREEN);
	// draw_dir_arrow(window, win_pos, player->dir);
	mat_free(win_pos);
	END();
}

static void	draw_dir_arrow(t_window *window, t_matrix *pos, t_matrix *dir)
{
	START();
	draw_line(window, pos, RED);
	//draw_circle(window, pos->values[0][0], pos->values[1][0], 3.0, RED);
	draw_circle(window, pos, 3.0, RED);
	END();
}

# define TMP_DELTA_T 0.01
static void	draw_line(t_window *window, t_matrix *pos, int color)
{
	t_matrix	*tmp;
	double		tmp_x;
	double		tmp_y;

	START();
	double t = TMP_DELTA_T;
	while (42)
	{
		tmp = mat_mul_scalar(t, pos);
		tmp_x = tmp->values[0][0];
		tmp_y = tmp->values[1][0];
		// 終了条件
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
	END();
}

// static void	draw_circle(t_window *window, double x, double y, double r, int color)
// {
// 	int	i;
// 	int	j;

// 	START();
// 	i = -r/2;
// 	while (i < r/2)
// 	{
// 		j = -r/2;
// 		while (j < r/2)
// 		{
// 			if (pow(x+i, 2.0) + pow(y+j, 2.0) <= pow(r, 2.0)) // 円の方程式
// 			{
// 				my_mlx_pixel_put(window->img, x+i, y+j, color);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	END();
// }

static void	draw_circle(t_window *window, t_matrix *center, double r_max, int color)
{
	const double	delta_r = 0.01;
	const double	delta_theta = 0.01;
	double	r;
	double	theta;

	r = 0;
	while (r <= r_max)
	{
		theta = 0;
		while (theta < M_PI * 2)
		{
			my_mlx_pixel_put(window->img, center->values[0][0] + (r * cos(theta)),
							center->values[1][0] + (r * sin(theta)), color);
			theta += delta_theta;
		}
		r += delta_r;
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
		plot_x = (ray->player->pos->values[0][0] + (t * ray->dir->values[0][0])) * MINIMAP_SIZE + MINIMAP_SIZE/2;
		plot_y = (ray->player->pos->values[1][0] + (t * ray->dir->values[1][0])) * MINIMAP_SIZE + MINIMAP_SIZE/2;
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

