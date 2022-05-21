#include "cub3d.h"

typedef struct s_raycastvar
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	double	half_step_x;
	double	half_step_y;
	double	euclid_dist;
	int		line_height;
	double	wall_x;
	int		draw_start;
	int		draw_end;
	t_texture	*tex;
	int			tex_x;
	double		tex_step;
}	t_raycastvar;

void	dump_lvar(t_raycastvar *lvar)
{
	if (lvar->x == WIN_W / 2) {
		fprintf(stderr, "-- dump lvar in render --\n");
		fprintf(stderr, "euclid_dist    %lf\n", lvar->euclid_dist);
		fprintf(stderr, "perp_wall_dist %lf\n", lvar->perp_wall_dist);
		fprintf(stderr, "wall_x         %lf\n", lvar->wall_x);
	}
}

typedef enum e_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}	t_side;

int	get_texture_color(const t_texture *tex, const int x, const int y);

double	subtend_angle(double dir1_x, double dir1_y, double dir2_x, double dir2_y)
{
	double	inner;
	double	norm1;
	double	norm2;

	inner = dir1_x * dir2_x + dir1_y * dir2_y;
	norm1 = sqrt(dir1_x * dir1_x + dir1_y * dir1_y);
	norm2 = sqrt(dir2_x * dir2_x + dir2_y * dir2_y);
	return (acos(inner / (norm1 * norm2)));
}

void	calc_ray_dirction(t_cub *cub, t_raycastvar *lvar)
{
	t_player	*player;

	player = cub->player;
	lvar->camera_x = 2 * lvar->x / (double)WIN_W - 1;
	lvar->ray_dir_x = player->dir_x + player->plane_x * lvar->camera_x;
	lvar->ray_dir_y = player->dir_y + player->plane_y * lvar->camera_x;
}

void	init_raycast_iterator(t_cub *cub, t_raycastvar *lvar)
{
	t_player		*player;

	player = cub->player;
	lvar->map_x = (int)(player->pos_x);
	lvar->map_y = (int)(player->pos_y);
	lvar->delta_dist_x = sqrt(1 + (lvar->ray_dir_y * lvar->ray_dir_y) / (lvar->ray_dir_x * lvar->ray_dir_x));
	lvar->delta_dist_y = sqrt(1 + (lvar->ray_dir_x * lvar->ray_dir_x) / (lvar->ray_dir_y * lvar->ray_dir_y));
	if (lvar->ray_dir_x < 0)
	{
		lvar->step_x = -1;
		lvar->side_dist_x = (player->pos_x - lvar->map_x) * lvar->delta_dist_x;
	}
	else
	{
		lvar->step_x = 1;
		lvar->side_dist_x = (lvar->map_x + 1.0 - player->pos_x) * lvar->delta_dist_x;
	}
	if (lvar->ray_dir_y < 0)
	{
		lvar->step_y = -1;
		lvar->side_dist_y = (player->pos_y - lvar->map_y) * lvar->delta_dist_y;
	}
	else
	{
		lvar->step_y = 1;
		lvar->side_dist_y = (lvar->map_y + 1.0 - player->pos_y) * lvar->delta_dist_y;
	}
}

void	cast_ray(t_cub *cub, t_raycastvar *lvar)
{
	t_player		*player;
	t_map			*map;

	player = cub->player;
	map = cub->map;
	while (true)
	{
		if (lvar->side_dist_x < lvar->side_dist_y)
		{
			lvar->side_dist_x += lvar->delta_dist_x;
			lvar->map_x += lvar->step_x;
			if (lvar->ray_dir_x > 0)
				lvar->side = NORTH;
			else
				lvar->side = SOUTH;
		}
		else
		{
			lvar->side_dist_y += lvar->delta_dist_y;
			lvar->map_y += lvar->step_y;
			if (lvar->ray_dir_y > 0)
				lvar->side = WEST;
			else
				lvar->side = EAST;
		}
		if (map->map[lvar->map_x][lvar->map_y].kind == WALL)
			break ;
		else if (map->map[lvar->map_x][lvar->map_y].kind == DOOR)
		{
			if (lvar->side == EAST || lvar->side == WEST)
			{
				double	half_step_y = 0.5f;
				if (lvar->ray_dir_y > 0)
					half_step_y = -0.5f;
				double	half_step_x = ((lvar->ray_dir_x / lvar->ray_dir_y) * half_step_y);
				lvar->euclid_dist = (lvar->side_dist_y - lvar->delta_dist_y);
				lvar->perp_wall_dist = lvar->euclid_dist * cos(subtend_angle(player->dir_x, player->dir_y, lvar->ray_dir_x, lvar->ray_dir_y));
				if (lvar->x == WIN_W / 2)
					lvar->perp_wall_dist = lvar->euclid_dist;
				double ray_head_x = player->pos_x + lvar->perp_wall_dist * lvar->ray_dir_x;
				double added_half_step_x = ray_head_x - half_step_x;

				double diff_time_in_sec = (gettimestamp() - cub->timestamp) / 100000.0;
				if (diff_time_in_sec < 0) {
					diff_time_in_sec = 0.000130;
				}
				if (map->map[lvar->map_x][lvar->map_y].door_state == OPENING) {
					map->map[lvar->map_x][lvar->map_y].timer += diff_time_in_sec;
					if (map->map[lvar->map_x][lvar->map_y].timer < 0.0) {
						map->map[lvar->map_x][lvar->map_y].timer = 0.0;
					}
					if (map->map[lvar->map_x][lvar->map_y].timer > 1.0) {
						map->map[lvar->map_x][lvar->map_y].timer = 1.0;
						map->map[lvar->map_x][lvar->map_y].door_state = OPEN;
					}
				}
				if (map->map[lvar->map_x][lvar->map_y].door_state == CLOSING) {
					map->map[lvar->map_x][lvar->map_y].timer -= diff_time_in_sec;
					if (map->map[lvar->map_x][lvar->map_y].timer > 1.0) {
						map->map[lvar->map_x][lvar->map_y].timer = 1.0;
					}
					if (map->map[lvar->map_x][lvar->map_y].timer < 0.0) {
						map->map[lvar->map_x][lvar->map_y].timer = 0.0;
						map->map[lvar->map_x][lvar->map_y].door_state = CLOSE;
					}
				}
				if ((int)added_half_step_x != lvar->map_x)
					continue;
				if ((int)(added_half_step_x - map->map[lvar->map_x][lvar->map_y].timer) == lvar->map_x)
				{
					lvar->side_dist_y += lvar->delta_dist_y * (0.5f);
					break ;
				}
			}
		}
	}
	if(lvar->side == NORTH || lvar->side == SOUTH)
		lvar->euclid_dist = (lvar->side_dist_x - lvar->delta_dist_x);
	else
		lvar->euclid_dist = (lvar->side_dist_y - lvar->delta_dist_y);

	lvar->perp_wall_dist = lvar->euclid_dist * cos(subtend_angle(player->dir_x, player->dir_y, lvar->ray_dir_x, lvar->ray_dir_y));
	if (lvar->x == WIN_W / 2)
		lvar->perp_wall_dist = lvar->euclid_dist;
}

void	draw_vertilcal_line(t_cub *cub, t_raycastvar *lvar)
{
	for (int i = 0; i < lvar->draw_start; i++) {
		put_pixel(cub, lvar->x, i, cub->map->ceil);
	}
	double	itr_tex_y = 0.0; // オフセットが必要
	if (-lvar->line_height / 2 + WIN_H / 2 + cub->camera->pitch < 0)
	{
		itr_tex_y += abs(-lvar->line_height / 2 + WIN_H / 2 + cub->camera->pitch) * lvar->tex_step;
	}
	for (int i = lvar->draw_start; i < lvar->draw_end; i++) {
		unsigned int color;
		int tex_y = (int)itr_tex_y;
		color = get_texture_color(lvar->tex, lvar->tex_x, tex_y);
		if (lvar->side == EAST || lvar->side == SOUTH)
			color = (color >> 1) & 0b011111110111111101111111; // be darker
		put_pixel(cub, lvar->x, i, color);
		itr_tex_y += lvar->tex_step;
	}
	for (int i = lvar->draw_end; i < WIN_H; i++) {
		put_pixel(cub, lvar->x, i, cub->map->floor);
	}
}

void	set_wall_texture(t_cub *cub, t_raycastvar *lvar)
{
	t_player	*player;
	t_map		*map;
	double		tex_x_on_map;

	player = cub->player;
	map = cub->map;
	if(lvar->side == NORTH || lvar->side == SOUTH)
		lvar->wall_x = player->pos_y + lvar->perp_wall_dist * lvar->ray_dir_y;
	else
		lvar->wall_x = player->pos_x + lvar->perp_wall_dist * lvar->ray_dir_x;
	if (lvar->side == WEST)
	{
		lvar->tex = map->west;
		tex_x_on_map = lvar->wall_x - (int)lvar->wall_x;
	}
	else if (lvar->side == EAST)
	{
		lvar->tex = map->east;
		tex_x_on_map = (1.0 - (lvar->wall_x - (int)lvar->wall_x));
	}
	else if (lvar->side == SOUTH)
	{
		lvar->tex = map->south;
		tex_x_on_map = lvar->wall_x - (int)lvar->wall_x;
	}
	else if (lvar->side == NORTH)
	{
		lvar->tex = map->north;
		tex_x_on_map = (1.0 - (lvar->wall_x - (int)lvar->wall_x));
	}
	lvar->tex_x = lvar->tex->width * tex_x_on_map;
	lvar->tex_step = lvar->tex->height / (double)lvar->line_height;
}

void	fill_perpbuf(t_cub *cub, t_raycastvar *lvar)
{
	cub->sprite->buf_perp[lvar->x] = lvar->perp_wall_dist;
}

void	set_draw_range(t_cub *cub, t_raycastvar *lvar)
{
	lvar->line_height = (int)(WIN_H / lvar->perp_wall_dist);
	lvar->draw_start = -lvar->line_height / 2 + WIN_H / 2 + cub->camera->pitch;
	if (lvar->draw_start < 0)
		lvar->draw_start = 0;
	lvar->draw_end = lvar->line_height / 2 + WIN_H / 2 + cub->camera->pitch;
	if (lvar->draw_end >= WIN_H)
		lvar->draw_end = WIN_H - 1;
}

void	draw_walls(t_cub *cub)
{
	t_raycastvar	lvar;

	lvar.x = -1;
	while (++lvar.x < WIN_W)
	{
		// dump_cub(cub);
		calc_ray_dirction(cub, &lvar);
		init_raycast_iterator(cub, &lvar);
		cast_ray(cub, &lvar);
		set_draw_range(cub, &lvar);
		set_wall_texture(cub, &lvar);
		draw_vertilcal_line(cub, &lvar);
		fill_perpbuf(cub, &lvar);
		dump_lvar(&lvar);
	}
}
