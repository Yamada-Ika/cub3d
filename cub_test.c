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
static void	ft_bzero(void *s, size_t n);
static void	*ft_calloc(size_t nmemb, size_t size);
static double	abs_double(double a);
static void	place_block(t_matrix *world_map, size_t place_i, size_t place_j);
static t_matrix	*gen_world_map();
static t_player	*gen_player(double pos_x, double pos_y,
							double dir_x, double dir_y);
static void	ft_raycast(t_ray *rays, t_matrix *world_map);
static void	render_3d(t_window *window, t_ray *rays);
static void	raycast_test(t_window *window);
static t_ray	*gen_rays(t_player *player);
static int	get_collision(t_ray *ray, double t, t_matrix *world_map);
static void	draw_line_v(t_window *window, t_matrix *center,
						size_t length, int color);
static int	idx_is_out_of_range(int idx, size_t limit);
static double	get_rotation_phi(double theta);

/*
int main()
{
	t_window	*window;
	t_game		game;

	window = init_window(WIN_W, WIN_H, WIN_TITLE);
	raycast_test(window);
	mlx_put_image_to_window(window->mlx,
							window->mlx_win,
							window->img,
							0, 0);
	set_hooks(window);
	mlx_loop(window->mlx);
	return (0);
}
*/

// draw_3d_imageとか？
void	get_3d_image(t_game *game)
{
	t_matrix	*world_map = game->map->map;
	t_player	*player = game->player;
	t_ray	*rays;

	rays = gen_rays(player);
	printf("gen_rays complete!\n");
	ft_raycast(rays, world_map);
	printf("raycast complete!\n");
	render_3d(game->window, rays);
	render_minimap(game->window, world_map, player, rays);
	printf("rendering complete!\n");
}

static t_matrix	*gen_world_map(void)
{
	const size_t usr_map_row = 6;
	const size_t usr_map_col = 5;
	char	usr_map[6][5] = {{1, 1, 1, 1, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{2, 0, 0, 0, 2},
							{1, 0, 0, 0, 1},
							{1, 1, 1, 1, 1}};
	t_matrix	*world_map;
	size_t	i;
	size_t	j;

	world_map = mat_new(usr_map_row, usr_map_col);
	i = 0;
	while (i < usr_map_row)
	{
		j = 0;
		while (j < usr_map_col)
		{
			world_map->values[i][j] = usr_map[i][j];
			++j;
		}
		++i;
	}
	return (world_map);
}

//return the array of the instances.
// インスタンス作成ならnew_raysの方が一般的かも
static t_ray	*gen_rays(t_player *player)
{
	const double	delta_theta = FOV / RAY_NUM;
	double			theta;
	int				i;
	t_matrix		*rot_mat;
	t_ray			*rays;

	rays = (t_ray *)ft_calloc(RAY_NUM, sizeof(t_ray)); // create_rays?
	i = 0;
	theta = 0;
	while (i < RAY_NUM)
	{
		(rays[i]).phi = get_rotation_phi(delta_theta * (double)i); // set_phi, set_angle, set_cast_angle, set_radiate_angle
		rot_mat = mat_rotation_2d((rays[i]).phi);
		//printf("ply dir:(%f, %f)\n", player->dir->values[0][0], player->dir->values[1][0]);
		(rays[i]).dir = mat_mul(rot_mat, player->dir); // set_direction
		//printf("ray dir:(%f, %f)\n", (rays[i].dir)->values[0][0], (rays[i].dir)->values[1][0]);
		(rays[i]).player = player; // set_cast_pos, set_radiate_pos, set_start_point
		mat_free(rot_mat);
		++i;
	}
	return (rays);
}

static double	get_rotation_phi(double theta)
{
	// return (atan((2 * tan(FOV / 2) * ((WIN_W / 2) - (int)i)) / WIN_W));
	// return (atan((2 * tan(FOV / 2) * ((IMG_PLANE_LEN / 2) - (int)i)) / IMG_PLANE_LEN));
	return ((FOV / 2.0) - theta);
}

static void	ft_raycast(t_ray *rays, t_matrix *world_map)
{
	size_t	ray_i;
	int		collide_status;
	double	t;

	ray_i = 0;
	while (ray_i < RAY_NUM)
	{
		t = DELTA_T;
		while (42)
		{
			//should use vertical l2 norm
			collide_status = get_collision(&rays[ray_i], t, world_map);
			if (collide_status != 0)
				break ;
			t += DELTA_T;
		}
		++ray_i;
	}
}

static int	get_collision(t_ray *ray, double t, t_matrix *world_map)
{
	int			res;
	t_matrix	*collide;
	t_matrix	*tmp;
	double	collide_x;
	double	collide_y;

	tmp = mat_mul_scalar(t, ray->dir);
	collide = mat_add(ray->player->pos, tmp);
	collide_x = collide->values[0][0];
	collide_y = collide->values[1][0];
	// printf("collide_x:%f, y:%f\n", collide_x, collide_y);
	if (idx_is_out_of_range(collide_x, world_map->col)
		|| idx_is_out_of_range(collide_y, world_map->row))
		res = -1;
	else if (world_map->values[(int)collide_y][(int)collide_x] > 0)
	{
		mat_free(tmp);
		tmp = mat_add(collide, mat_mul_scalar(-1, ray->player->pos));
		ray->v_distance = abs_double((mat_distance_2d(tmp) * cos(ray->phi)) 
							- (IMG_PLANE_LEN / (2 * tan(FOV / 2.0))));
		if (world_map->values[(int)collide_y][(int)collide_x] == 1)
			ray->color = RED;
		if (world_map->values[(int)collide_y][(int)collide_x] == 2)
		{
			// printf("blue!!\n");
			ray->color = BLUE;
		}
		res = 1;
	}
	else
		res = 0;
	mat_free(collide);
	return (res);
}

static void	render_3d(t_window *window, t_ray *rays)
{
	size_t		ray_i;
	size_t		line_length;
	int			line_color;
	t_matrix	*center_of_line;

	ray_i = 0;
	while (ray_i < RAY_NUM)
	{
		center_of_line = mat_vector_col_2d(RAY_NUM - ray_i - 1, WIN_H / 2);
		line_length = (size_t)(1000 / (1.0 + rays[ray_i].v_distance));
		line_color = rays[ray_i].color;
		//printf("center:(%d, %d) length:%zu\n", (int)center_of_line->values[0][0], (int)center_of_line->values[0][1], line_length);
		draw_line_v(window, center_of_line, line_length, line_color);
		++ray_i;
	}
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
			my_mlx_pixel_put(window->img, start_x, start_y + (int)i, color);
		if (!idx_is_out_of_range(start_y - i, WIN_H))
			my_mlx_pixel_put(window->img, start_x, start_y - (int)i, color);
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
	if (idx < 0 || idx > limit)
		return (1);
	else
		return (0);
}

/* libft */
static void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	res = malloc(size * nmemb);
	if (res == NULL)
		exit_with_error(MALLOC_ERR, 1);
	ft_bzero(res, size * nmemb);
	return (res);
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*uc_s;
	size_t			i;

	uc_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		uc_s[i] = 0;
		++i;
	}
}
