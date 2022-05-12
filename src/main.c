#include "cub3d.h"

typedef enum e_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}	t_side;

// vector data structure
typedef struct s_vector
{
	char	**data;
	size_t	cap; // メモリ領域の長さ
	size_t	len; // データが詰まってるサイズ
}	t_vector;

typedef struct s_config
{
	char	**cub;
	long long	seek;
	char	*no_tex_path;
	char	*so_tex_path;
	char	*we_tex_path;
	char	*ea_tex_path;
	t_vector	*sp_texs;
	long long sp_num;
	int		floor_color;
	int		ceil_color;
	int		**map;
	long long	height;
	long long	width;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_config;

typedef enum e_error
{
	NO_ERR,
	INVALID_ARG_NUM_ERR,
	INVALID_CUB_FILE,
	CUB_FILE_ERR,
	MEM_ERR,
	TEX_FILE_ERR,
	INVALID_RGB,
	NON_CLOSED_MAP,
	NON_PLAYER,
}	t_error;

// ------------------- dump -------------------
void	dump_cub(t_cub *cub);
void	dump_config(t_config *config);

// -------------- mlx wrapper --------------
void	put_pixel(t_cub *cub, int x, int y, unsigned int color)
{
	my_mlx_pixel_put(cub->window->img_front, x, y, color);
}

void	put_image(t_cub *cub)
{
	mlx_put_image_to_window(cub->window->mlx,
						cub->window->mlx_win,
						cub->window->img_front->img,
						0, 0);
}

int	get_texture_color(const t_texture *tex, const int x, const int y)
{
	return (*(int *)(tex->img->addr + (y * tex->img->line_length + x * (tex->img->bits_per_pixel / 8))));
}

void	swap_sprite(t_sprite *lhs, t_sprite *rhs)
{
	t_sprite	tmp;

	tmp.x = lhs->x;
	tmp.y = lhs->y;
	tmp.tex = lhs->tex;
	tmp.dist_from_player = lhs->dist_from_player;
	lhs->x = rhs->x;
	lhs->y = rhs->y;
	lhs->tex = rhs->tex;
	lhs->dist_from_player = rhs->dist_from_player;
	rhs->x = tmp.x;
	rhs->y = tmp.y;
	rhs->tex = tmp.tex;
	rhs->dist_from_player = tmp.dist_from_player;
}

void	render(t_cub *cub)
{
	double pos_x = cub->player->pos_x;
	double pos_y = cub->player->pos_y;
	double dir_x = cub->player->dir_x;
	double dir_y = cub->player->dir_y;
	double plane_x = cub->player->plane_x;
	double plane_y = cub->player->plane_y;

	dump_cub(cub);

	for(int x = 0; x < WIN_W; x++)
	{
		//calculate ray position and direction
		double camera_x = 2 * x / (double)WIN_W - 1; //x-coordinate in camera space
		double ray_dir_x = dir_x + plane_x * camera_x;
		double ray_dir_y = dir_y + plane_y * camera_x;

		//which box of the map we're in
		int map_x = (int)(pos_x);
		int map_y = (int)(pos_y);

		//length of ray from current position to next x or y-side
		double side_dist_x;
		double side_dist_y;

		//length of ray from one x or y-side to next x or y-side
		// double delta_dist_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
		// double delta_dist_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
		double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
		double perp_wall_dist;

		//what direction to step in x or y-direction (either +1 or -1)
		int step_x;
		int step_y;

		bool has_hit = false; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
		}

		//perform DDA
		while (!has_hit)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				if (ray_dir_x > 0)
					side = NORTH;
				else
					side = SOUTH;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				if (ray_dir_y > 0)
					side = WEST;
				else
					side = EAST;
			}
			//Check if ray has hit a wall
			if (cub->map->map[map_x][map_y] > 0)
				has_hit = true;
		}

		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(side == NORTH || side == SOUTH)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);

		//Calculate height of line to draw on screen
		int line_height = (int)(WIN_H / perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		int draw_start = -line_height / 2 + WIN_H / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + WIN_H / 2;
		if (draw_end >= WIN_H)
			draw_end = WIN_H - 1;

		//choose wall color
		// calculate value of wall_x
		double	wall_x;
		if(side == NORTH || side == SOUTH)
			wall_x = pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = pos_x + perp_wall_dist * ray_dir_x;

		double	tex_x_on_map;
		t_texture	*tex;
		if (side == WEST)
		{
			tex = cub->map->west;
			tex_x_on_map = wall_x - (int)wall_x;
		}
		else if (side == EAST)
		{
			tex = cub->map->east;
			tex_x_on_map = (1.0 - (wall_x - (int)wall_x));
		}
		else if (side == SOUTH)
		{
			tex = cub->map->south;
			tex_x_on_map = wall_x - (int)wall_x;
		}
		else if (side == NORTH)
		{
			tex = cub->map->north;
			tex_x_on_map = (1.0 - (wall_x - (int)wall_x));
		}
		int	tex_x = tex->width * tex_x_on_map;
		double	tex_step = tex->height / (double)line_height;

		// dump
		if (x == WIN_W/2) {
			char *side_kw[] = {"NORTH", "SOUTH", "WEST", "EAST"};
			fprintf(stderr, "-- dump var in draw --\n");
			fprintf(stderr, "ray index       : %d\n", x);
			fprintf(stderr, "side            : %d\n", side);
			fprintf(stderr, "side            : %s\n", side_kw[side]);
			fprintf(stderr, "pos_x           : %f\n", pos_x);
			fprintf(stderr, "pos_y           : %f\n", pos_y);
			fprintf(stderr, "ray_dir_x       : %f\n", ray_dir_x);
			fprintf(stderr, "ray_dir_y       : %f\n", ray_dir_y);
			fprintf(stderr, "perp_wall_dist  : %f\n", perp_wall_dist);
			fprintf(stderr, "ray_dir_y       : %f\n", ray_dir_y);
			fprintf(stderr, "wall_x          : %f\n", wall_x);
			fprintf(stderr, "tex_x           : %d\n", tex_x);
			fprintf(stderr, "tex->width      : %d\n", tex->width);
			fprintf(stderr, "tex->height     : %d\n", tex->height);
			fprintf(stderr, "line_height     : %d\n", line_height);
			fprintf(stderr, "tex_step        : %f\n", tex_step);
		}

		// fill buffer
		for (int i = 0; i < draw_start; i++) {
			put_pixel(cub, x, i, cub->map->ceil);
		}
		double	itr_tex_y = 0.0;
		for (int i = draw_start; i < draw_end; i++) {
			unsigned int color;
			int tex_y = (int)itr_tex_y;
			color = get_texture_color(tex, tex_x, tex_y);
			if (side == EAST || side == SOUTH)
				color = (color >> 1) & 0b011111110111111101111111; // be darker
			put_pixel(cub, x, i, color);
			itr_tex_y += tex_step;
		}
		for (int i = draw_end; i < WIN_H; i++) {
			put_pixel(cub, x, i, cub->map->floor);
		}

		// fill perp-buffer
		cub->sprite->buf_perp[x] = perp_wall_dist;
	}

	t_sprite	*sprites = cub->sprite->sprites;
	// spriteの距離を計算
	for (int i = 0; i < cub->sprite->num; i++) {
		double	sp_pos_x = sprites[i].x;
		double	sp_pos_y = sprites[i].y;
		sprites[i].dist_from_player = (sp_pos_x - pos_x) * (sp_pos_x - pos_x) + (sp_pos_y - pos_y) * (sp_pos_y - pos_y);
	}

	// 距離で降順にソート
	while (true) {
		bool	has_swap = false;

		for (int i = 0; i < cub->sprite->num - 1; i++) {
			if (sprites[i].dist_from_player < sprites[i + 1].dist_from_player) {
				swap_sprite(&sprites[i], &sprites[i + 1]);
				has_swap = true;
			}
		}
		if (!has_swap)
			break ;
	}

	for (int i = 0; i < cub->sprite->num; i++) {
		// プレイヤーからの相対位置
		double	rsp_pos_x = sprites[i].x - pos_x;
		double	rsp_pos_y = sprites[i].y - pos_y;

		// transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]
		double	inv_det = 1 / (plane_x * dir_y - dir_x * plane_y);

		// transform camera cordinate
		double	trans_x = inv_det * (dir_y * rsp_pos_x + (-dir_x) * rsp_pos_y);
		double	trans_y = inv_det * ((-plane_x) * rsp_pos_x + plane_x * rsp_pos_y);

		// sprite x on window
		int	sprite_x_on_window = (WIN_W / 2) * (trans_x / trans_y + 1);

		fprintf(stderr, "-- dump sprite var --\n");
		fprintf(stderr, "sprites[%d].x            %lf\n", i, sprites[i].x);
		fprintf(stderr, "sprites[%d].y            %lf\n", i, sprites[i].y);
		fprintf(stderr, "pos_x                    %lf\n", pos_x);
		fprintf(stderr, "pos_y                    %lf\n", pos_y);
		fprintf(stderr, "rsp_pos_x                %lf\n", rsp_pos_x);
		fprintf(stderr, "rsp_pos_y                %lf\n", rsp_pos_y);
		fprintf(stderr, "plane_x                  %lf\n", plane_x);
		fprintf(stderr, "plane_y                  %lf\n", plane_y);
		fprintf(stderr, "dir_y                    %lf\n", dir_y);
		fprintf(stderr, "dir_x                    %lf\n", dir_x);
		fprintf(stderr, "inv_det                  %lf\n", inv_det);
		fprintf(stderr, "trans_x                  %lf\n", trans_x);
		fprintf(stderr, "trans_y                  %lf\n", trans_y);
		fprintf(stderr, "trans_x/trans_y          %lf\n", trans_x / trans_y);
		fprintf(stderr, "sprite_x_on_window       %d\n", sprite_x_on_window);

		// calculate height of the sprite on screen
		int	sprite_height = abs((int)(WIN_H / trans_y));

		// calculate lowest and heighest pixel to fill in current sprite
		int	draw_start_y = -sprite_height / 2 + WIN_H / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		int	draw_end_y = sprite_height / 2 + WIN_H / 2;
		if (draw_end_y >= WIN_H)
			draw_end_y = WIN_H - 1;
		
		// calculate width of sprite
		int	sprite_width = abs((int)(WIN_H / trans_y));
		int	draw_start_x = -sprite_width / 2 + sprite_x_on_window;
		if (draw_start_x < 0)
			draw_start_x = 0;
		int	draw_end_x = sprite_width / 2 + sprite_x_on_window;
		if (draw_end_x >= WIN_W)
			draw_end_x = WIN_W - 1;

		// loop through every vertical stripe of the sprite on screen
		double	step_sprite_tex_x = sprites[i].tex->width / (double)sprite_width;
		double	step_sprite_tex_y = sprites[i].tex->height / (double)sprite_height;

		fprintf(stderr, "draw_start_x            %d\n", draw_start_x);
		fprintf(stderr, "draw_end_x              %d\n", draw_end_x);
		fprintf(stderr, "step_sprite_tex_x       %lf\n", step_sprite_tex_x);
		fprintf(stderr, "step_sprite_tex_y       %lf\n", step_sprite_tex_y);

		double	itr_x = 0.0;
		double	itr_y = 0.0;

		// !TODO Should be more simple
		if (-sprite_width / 2 + sprite_x_on_window < 0) {
			itr_x = -(-sprite_width / 2 + sprite_x_on_window); // offset
		}

		for (int x = draw_start_x; x < draw_end_x; x++) {
			// !TODO If possible, cut this
			if (trans_y <= 0 || x < 0 || WIN_W < x || trans_y >= cub->sprite->buf_perp[x]) {
				itr_x += step_sprite_tex_x;
				continue ;
			}

			itr_y = 0.0;
			for (int y = draw_start_y; y < draw_end_y; y++) {
				int	tex_x = (int)itr_x;
				int	tex_y = (int)itr_y;

				itr_y += step_sprite_tex_y;
				if (tex_x > sprites[i].tex->width || tex_y > sprites[i].tex->height)
					continue ;
				unsigned int color = get_texture_color(sprites[i].tex, tex_x, tex_y);

				if (color == 0x000000) {
					continue ;
				}
				put_pixel(cub, x, y, color);
			}
			itr_x += step_sprite_tex_x;
		}
	}

	put_image(cub);
}

bool	can_move(int keycode, t_cub *cub)
{
	if (keycode == W_KEY) // move forward
	{
		// collide wall ?
		if (cub->map->map[(int)(cub->player->pos_x)][(int)(cub->player->pos_y + cub->player->dir_y * MOVE_STEP)] != 0)
			return (false);
		cub->player->pos_y += cub->player->dir_y * MOVE_STEP;
		if (cub->map->map[(int)(cub->player->pos_x + cub->player->dir_x * MOVE_STEP)][(int)(cub->player->pos_y)] != 0)
			return (false);
		cub->player->pos_x += cub->player->dir_x * MOVE_STEP;
		return (true);
	}
	if (keycode == S_KEY) // move back
	{
		// collide wall ?
		if (cub->map->map[(int)(cub->player->pos_x)][(int)(cub->player->pos_y - cub->player->dir_y * MOVE_STEP)] != 0)
			return (false);
		cub->player->pos_y -= cub->player->dir_y * MOVE_STEP;
		if (cub->map->map[(int)(cub->player->pos_x-cub->player->dir_x * MOVE_STEP)][(int)(cub->player->pos_y)] != 0)
			return (false);
		cub->player->pos_x -= cub->player->dir_x * MOVE_STEP;
		return (true);
	}
	if (keycode == R_ARROW) // see right
	{
		double old_dir_x = cub->player->dir_x;
		cub->player->dir_x = cub->player->dir_x * cos(-ROT_STEP) - cub->player->dir_y * sin(-ROT_STEP);
		cub->player->dir_y = old_dir_x * sin(-ROT_STEP) + cub->player->dir_y * cos(-ROT_STEP);
		double old_plane_x = cub->player->plane_x;
		cub->player->plane_x = cub->player->plane_x * cos(-ROT_STEP) - cub->player->plane_y * sin(-ROT_STEP);
		cub->player->plane_y = old_plane_x * sin(-ROT_STEP) + cub->player->plane_y * cos(-ROT_STEP);
		return (true);
	}
	if (keycode == L_ARROW) // see left
	{
		double old_dir_x = cub->player->dir_x;
		cub->player->dir_x = cub->player->dir_x * cos(ROT_STEP) - cub->player->dir_y * sin(ROT_STEP);
		cub->player->dir_y = old_dir_x * sin(ROT_STEP) + cub->player->dir_y * cos(ROT_STEP);
		double old_plane_x = cub->player->plane_x;
		cub->player->plane_x = cub->player->plane_x * cos(ROT_STEP) - cub->player->plane_y * sin(ROT_STEP);
		cub->player->plane_y = old_plane_x * sin(ROT_STEP) + cub->player->plane_y * cos(ROT_STEP);
		return (true);
	}
	return (false);
}

int	handle_key_hook(int keycode, void *params)
{
	t_cub	*cub;

	fprintf(stderr, "keycode : %d\n", keycode);

	cub = (t_cub *)params;
	if (keycode == ESC)
		exit(0);
	if (can_move(keycode, cub))
	{
		render(cub);
	}
}

#include <X11/X.h>

void	set_hooks(t_cub *cub)
{
	// mlx_key_hook(cub->window->mlx_win, handle_key_hook, cub);
	mlx_hook(cub->window->mlx_win, KeyPress, KeyPressMask, handle_key_hook, cub);
}

// ----------------- parser -----------------

char	*concat(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

t_error	load_cub(t_config *config, const char *path)
{
	int	fd;
	char	*read_line;
	char	*whole_line;

	fprintf(stderr, "load cub file ...\n");
	fd = open(path, O_RDONLY);
	whole_line = ft_strdup("");
	while (true)
	{
		read_line = get_next_line(fd);
		if (read_line == NULL)
			break ;
		whole_line = concat(whole_line, read_line);
		if (whole_line == NULL)
			break ;
	}
	close(fd);
	config->cub = ft_split2(whole_line, '\n');
	if (config->cub == NULL)
		return (MEM_ERR);
	return (NO_ERR);
}

t_error	set_tex_path(t_config *config)
{
	char	**file;
	size_t	i;
	int		flag;

	fprintf(stderr, "load texture path ...\n");
	file = config->cub;
	flag = 0;
	i = 0;
	while (file[i] != NULL)
	{
		if (flag == (1<<1 | 1<<2 | 1<<3 | 1<<4))
			break ;
		if (ft_strncmp(file[i], "NO", 2) == 0)
		{
			config->no_tex_path = ft_substr(file[i], 3, ft_strlen(file[i]));
			flag |= 1<<1;
		}
		if (ft_strncmp(file[i], "SO", 2) == 0)
		{
			config->so_tex_path = ft_substr(file[i], 3, ft_strlen(file[i]));
			flag |= 1<<2;
		}
		if (ft_strncmp(file[i], "WE", 2) == 0)
		{
			config->we_tex_path = ft_substr(file[i], 3, ft_strlen(file[i]));
			flag |= 1<<3;
		}
		if (ft_strncmp(file[i], "EA", 2) == 0)
		{
			config->ea_tex_path = ft_substr(file[i], 3, ft_strlen(file[i]));
			flag |= 1<<4;
		}
		i++;
	}
	config->seek = i + 1;
	return (NO_ERR);
}

t_error	set_color(t_config *config)
{
	char	**file;
	size_t	i;
	int		flag;
	char	*end;

	fprintf(stderr, "load color ...\n");
	file = config->cub;
	flag = 0;
	i = 0;
	while (file[i] != NULL)
	{
		if (flag == (1<<1 | 1<<2))
			break ;
		if (ft_strncmp(file[i], "F", 1) == 0)
		{
			int color = ft_strtoll(&file[i][1], &end, 10) << 16;
			end++; // skip ','
			color |= ft_strtoll(end, &end, 10) << 8;
			end++; // skip ','
			color |= ft_strtoll(end, &end, 10);
			config->floor_color = color;
			flag |= 1<<1;
		}
		if (ft_strncmp(file[i], "C", 1) == 0)
		{
			int color = ft_strtoll(&file[i][1], &end, 10) << 16;
			end++; // skip ','
			color |= ft_strtoll(end, &end, 10) << 8;
			end++; // skip ','
			color |= ft_strtoll(end, &end, 10);
			config->ceil_color = color;
			flag |= 1<<2;
		}
		i++;
	}
	config->seek = i + 1;
	return (NO_ERR);
}

t_error	set_map(t_config *config)
{
	char	**file;
	size_t	i;
	int		flag;
	char	*end;

	fprintf(stderr, "load map ...\n");
	file = config->cub;
	i = config->seek;
	// mapの上に改行があればスキップ
	while (file[i] != NULL)
	{
		if (ft_strcmp(file[i], "") == 0)
			continue ;
		else
			break ;
	}

	long long height = 0;
	long long width = 0;
	size_t idx = i;
	while (file[i+1] != NULL)
	{
		height++;
		i++;
	}
	width = ft_strlen(file[idx]);
	int	**map = malloc(height * sizeof(int *));
	config->map = map;
	config->height = height;
	config->width = width;
	for (int i = 0; i < height; i++)
	{
		map[i] = malloc(width * sizeof(int));
	}
	size_t j;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (file[idx][j] == 'N')
			{
				// set player info
				config->dir_x = -1;
				config->dir_y = 0;
				config->pos_x = i;
				config->pos_y = j;
				config->plane_x = 0;
				config->plane_y = 0.66;
				map[i][j] = 0;
				j++;
				continue ;
			}
			if (file[idx][j] == 'S')
			{
				// set player info
				config->dir_x = 1;
				config->dir_y = 0;
				config->pos_x = i;
				config->pos_y = j;
				config->plane_x = 0;
				config->plane_y = -0.66;
				map[i][j] = 0;
				j++;
				continue ;
			}
			if (file[idx][j] == 'E')
			{
				// set player info
				config->dir_x = 0;
				config->dir_y = 1;
				config->pos_x = i;
				config->pos_y = j;
				config->plane_x = 0.66;
				config->plane_y = 0;
				map[i][j] = 0;
				j++;
				continue ;
			}
			if (file[idx][j] == 'W')
			{
				// set player info
				config->dir_x = 0;
				config->dir_y = -1;
				config->pos_x = i;
				config->pos_y = j;
				config->plane_x = -0.66;
				config->plane_y = 0;
				map[i][j] = 0;
				j++;
				continue ;
			}
			map[i][j] = file[idx][j] - '0';
			j++;
		}
		idx++;
		i++;
	}
	return (NO_ERR);
}

void	vec_delete(t_vector *vec)
{
	size_t	i;

	i = 0;
	while (i < vec->len)
	{
		free(vec->data[i]);
		i++;
	}
	free(vec->data);
	free(vec);
}

void	vec_delete_data(char **data, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(data[i]);
		i++;
	}
	free(data);
}

void	vec_datacopy(t_vector *dst, char **data, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst->data[i] = ft_strdup(data[i]);
		i++;
	}
}

t_vector	*vec_push_back(t_vector *dst, char *elem)
{
	if (dst == NULL || dst->data == NULL)
	{
		t_vector	*new;

		new = ft_calloc(1, sizeof(t_vector));
		new->data = ft_calloc(128, sizeof(char **));
		new->cap = 128;
		dst = new;
	}
	if (dst->cap == dst->len)
	{
		// realloc的な
		t_vector *tmp = dst;
		size_t	old_len = dst->len;
		size_t	old_cap = dst->cap;

		dst = ft_calloc(1, sizeof(t_vector));
		dst->data = ft_calloc(old_cap + 128, sizeof(char **));
		dst->cap = old_cap + 128;
		dst->len = old_len;
		vec_datacopy(dst, tmp->data, old_len);
		vec_delete(tmp);
	}
	dst->data[dst->len] = ft_strdup(elem);
	dst->len++;
	return (dst);
}

t_error	set_sprite_path(t_config *config)
{
	char	**file;
	size_t	i;
	int		flag;
	char	*end;

	fprintf(stderr, "load sprite texture paths ...\n");
	file = config->cub;
	flag = 0;
	i = 0;
	config->sp_num = 0;
	config->sp_texs = ft_calloc(1, sizeof(t_vector));
	while (file[i] != NULL)
	{
		if (ft_strncmp(file[i], "S ", 2) == 0)
		{
			config->sp_texs = vec_push_back(config->sp_texs, &file[i][2]);
			config->sp_num++;
		}
		i++;
	}
	return (NO_ERR);
}

int	parse(int argc, char **argv, t_config *config)
{
	t_error	err;

	fprintf(stderr, "parse argument ...\n");
	if (argc != 2)
		return (INVALID_ARG_NUM_ERR);
	err = load_cub(config, argv[1]);
	if (err != NO_ERR)
		return (err);
	err = set_tex_path(config);
	if (err != NO_ERR)
		return (err);
	err = set_sprite_path(config);
	if (err != NO_ERR)
		return (err);
	err = set_color(config);
	if (err != NO_ERR)
		return (err);
	err = set_map(config);
	if (err != NO_ERR)
		return (err);
	return (NO_ERR);
}

// ----------------- parser -----------------

t_texture	*new_texture(t_cub *cub, char *file)
{
	t_texture	*tex;

	tex = ft_calloc(1, sizeof(t_texture));
	if (tex == NULL)
		return (NULL);
	tex->img = ft_calloc(1, sizeof(t_img));
	if (tex->img == NULL)
		return (NULL);
	tex->img->img = mlx_xpm_file_to_image(cub->window->mlx, file, &tex->width, &tex->height);
	if (tex->img->img == NULL)
		return (NULL);
	tex->img->addr = mlx_get_data_addr(tex->img->img, &tex->img->bits_per_pixel, &tex->img->line_length, &tex->img->endian);
	return (tex);
}

t_error	parseConfig(t_config *config, t_cub *cub)
{
	// player
	cub->player = ft_calloc(1, sizeof(t_player));
	cub->player->pos_x = config->pos_x;
	cub->player->pos_y = config->pos_y;
	cub->player->dir_x = config->dir_x;
	cub->player->dir_y = config->dir_y;
	cub->player->plane_x = config->plane_x;
	cub->player->plane_y = config->plane_y;

	// map
	cub->map = ft_calloc(1, sizeof(t_map));
	cub->map->map = config->map;
	cub->map->width = config->width;
	cub->map->heigth = config->height;

	// floor and ceil color
	cub->map->floor = config->floor_color;
	cub->map->ceil = config->ceil_color;

	// texture
	cub->map->north = new_texture(cub, config->no_tex_path);
	cub->map->south = new_texture(cub, config->so_tex_path);
	cub->map->east = new_texture(cub, config->ea_tex_path);
	cub->map->west = new_texture(cub, config->we_tex_path);

	// sprite
	// !TODO How to define sprite position
	cub->sprite = ft_calloc(1, sizeof(t_sprite_info));
	cub->sprite->num = config->sp_num;
	cub->sprite->sprites = ft_calloc(config->sp_num, sizeof(t_sprite));
	cub->sprite->buf_perp = ft_calloc(WIN_W, sizeof(double));
	for (int i = 0; i < config->sp_num; i++) {
		cub->sprite->sprites->tex = new_texture(cub, config->sp_texs->data[i]);
		// sprite_position_generator(cub);
		cub->sprite->sprites->x = 10.0f;
		cub->sprite->sprites->y = 15.0f;
		// cub->sprite->sprites[i].tex = new_texture(cub, config->sp_texs->data[i]);
		// // sprite_position_generator(cub);
		// cub->sprite->sprites[i].x = 10.0f;
		// cub->sprite->sprites[i].y = 15.0f;
	}
	return (NO_ERR);
}

int	main(int argc, char **argv)
{
	t_cub		cub;
	t_config	config;
	t_error		err;

	err = parse(argc, argv, &config);
	if (err != NO_ERR)
	{
		fprintf(stderr, "%d\n", err);
		return (1);
	}

	dump_config(&config); // dump

	cub.window = init_window(WIN_W, WIN_H, "cub3d");
	// cub.buf = ft_calloc(WIN_H, sizeof(unsigned int));

	err = parseConfig(&config, &cub);
	if (err != NO_ERR)
	{
		fprintf(stderr, "%d\n", err);
		return (1);
	}

	dump_cub(&cub); // dump

	render(&cub);
	set_hooks(&cub);
	mlx_loop(cub.window->mlx);
}

// ------------------------ dump ------------------------

void	dump_cub(t_cub *cub)
{
	fprintf(stderr, "-- dump cub head --\n");
	fprintf(stderr, "-- player info --\n");
	fprintf(stderr, "position  (%f, %f)\n", cub->player->pos_x, cub->player->pos_y);
	fprintf(stderr, "direction (%f, %f)\n", cub->player->dir_x, cub->player->dir_y);
	fprintf(stderr, "plane     (%f, %f)\n", cub->player->plane_x, cub->player->plane_y);
	fprintf(stderr, "-- map info --\n");
	for (int i = 0; i < cub->map->heigth; i++) {
		for (int j = 0; j < cub->map->width; j++) {
			// sprite
			bool	has_put = false;
			for (int n = 0; n < cub->sprite->num; n++) {
				if (i == (int)cub->sprite->sprites[n].x && j == (int)cub->sprite->sprites[n].y) {
					fprintf(stderr, ".");
					break ;
				}
			}
			if (has_put)
				continue ;
			if (i == (int)(cub->player->pos_x) && j == (int)(cub->player->pos_y))
				fprintf(stderr, "P");
			else if (cub->map->map[i][j] == 0)
				fprintf(stderr, " ");
			else
				fprintf(stderr, "█");
			if (j == cub->map->width -1)
				fprintf(stderr, "\n");
		}
	}
	fprintf(stderr, "-- color info --\n");
	fprintf(stderr, "floor   %x\n", cub->map->floor);
	fprintf(stderr, "ceil    %x\n", cub->map->ceil) ;
	fprintf(stderr, "-- texture info --\n");
	fprintf(stderr, "north side %p\n", cub->map->north);
	fprintf(stderr, "width %d, height %d\n", cub->map->north->height, cub->map->north->width);
	fprintf(stderr, "south side %p\n", cub->map->south);
	fprintf(stderr, "width %d, height %d\n", cub->map->south->height, cub->map->south->width);
	fprintf(stderr, "east side  %p\n", cub->map->east);
	fprintf(stderr, "width %d, height %d\n", cub->map->east->height, cub->map->east->width);
	fprintf(stderr, "west side  %p\n", cub->map->west);
	fprintf(stderr, "width %d, height %d\n", cub->map->west->height, cub->map->west->width);
	fprintf(stderr, "-- sprite info --\n");
	fprintf(stderr, "num %d\n", cub->sprite->num);
	for (int i = 0; i < cub->sprite->num; i++) {
		fprintf(stderr, "x                     %f\n", cub->sprite->sprites[i].x);
		fprintf(stderr, "y                     %f\n", cub->sprite->sprites[i].y);
		fprintf(stderr, "dist_from_player %f\n", cub->sprite->sprites[i].dist_from_player);
	}
	fprintf(stderr, "-- dump cub tail --\n");
}

void	dump_config(t_config *config)
{
	fprintf(stderr, "-- dump config head --\n");
	for (int i = 0; config->cub[i] != NULL; i++) {
		fprintf(stderr, "[%s]\n", config->cub[i]);
	}
	fprintf(stderr, "north texture path : [%s]\n", config->no_tex_path);
	fprintf(stderr, "south texture path : [%s]\n", config->so_tex_path);
	fprintf(stderr, "west  texture path : [%s]\n", config->we_tex_path);
	fprintf(stderr, "east  texture path : [%s]\n", config->ea_tex_path);
	fprintf(stderr, "floor color        : [%x]\n", config->floor_color);
	fprintf(stderr, "ceil color         : [%x]\n", config->ceil_color);
	fprintf(stderr, "sprite num         : [%lld]\n", config->sp_num);
	for (int i = 0; i < config->sp_num; i++) {
		fprintf(stderr, "sprite texture path: [%s]\n", config->sp_texs->data[i]);
	}
	fprintf(stderr, "player dir_x       : [%f]\n", config->dir_x);
	fprintf(stderr, "player dir_y       : [%f]\n", config->dir_y);
	fprintf(stderr, "player pos_x       : [%f]\n", config->pos_x);
	fprintf(stderr, "player pos_y       : [%f]\n", config->pos_y);
	fprintf(stderr, "map height         : [%lld]\n", config->height);
	fprintf(stderr, "map width          : [%lld]\n", config->width);
	fprintf(stderr, "-- dump map --\n");
	for (long long i = 0; i < config->height; i++) {
		for (long long j = 0; j < config->width; j++) {
			fprintf(stderr, "%d", config->map[i][j]);
			if (j == config->width - 1)
				fprintf(stderr, "\n");
		}
	}
	fprintf(stderr, "-- dump config tail --\n");
}
