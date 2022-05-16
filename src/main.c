#include "cub3d.h"
#include "parse.h"

typedef enum e_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}	t_side;

// ------------------- dump -------------------
void	dump_cub(t_cub *cub);
void	dump_config(t_config *config);

// ------------------- hooks -------------------
void	set_hooks(t_cub *cub);

//------------------- parse -------------------
int	parse_arg(int argc, char **argv, t_config *config);
t_error	parse_config(t_config *config, t_cub *cub);

void	draw_minimap(t_cub *cub);

int	get_texture_color(const t_texture *tex, const int x, const int y)
{
	return (*(int *)(tex->img->addr + (y * tex->img->line_length + x * (tex->img->bits_per_pixel / 8))));
}

void	swap_sprite(t_sprite *lhs, t_sprite *rhs)
{
	t_sprite	tmp;

	tmp.x = lhs->x;
	tmp.y = lhs->y;
	tmp.textures = lhs->textures;
	tmp.dist_from_player = lhs->dist_from_player;
	lhs->x = rhs->x;
	lhs->y = rhs->y;
	lhs->textures = rhs->textures;
	lhs->dist_from_player = rhs->dist_from_player;
	rhs->x = tmp.x;
	rhs->y = tmp.y;
	rhs->textures = tmp.textures;
	rhs->dist_from_player = tmp.dist_from_player;
}

// for calcluate frame index
long long time_in_ms() {
	t_time tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

long long time_in_500ms() {
	t_time tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000) / 500;
}

int	calc_frame_index(int frame_len)
{
	return (time_in_500ms() % frame_len);
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

		// // dump
		// if (x == WIN_W/2) {
		// 	char *side_kw[] = {"NORTH", "SOUTH", "WEST", "EAST"};
		// 	fprintf(stderr, "-- dump var in draw --\n");
		// 	fprintf(stderr, "ray index       : %d\n", x);
		// 	fprintf(stderr, "side            : %d\n", side);
		// 	fprintf(stderr, "side            : %s\n", side_kw[side]);
		// 	fprintf(stderr, "pos_x           : %f\n", pos_x);
		// 	fprintf(stderr, "pos_y           : %f\n", pos_y);
		// 	fprintf(stderr, "ray_dir_x       : %f\n", ray_dir_x);
		// 	fprintf(stderr, "ray_dir_y       : %f\n", ray_dir_y);
		// 	fprintf(stderr, "perp_wall_dist  : %f\n", perp_wall_dist);
		// 	fprintf(stderr, "ray_dir_y       : %f\n", ray_dir_y);
		// 	fprintf(stderr, "wall_x          : %f\n", wall_x);
		// 	fprintf(stderr, "tex_x           : %d\n", tex_x);
		// 	fprintf(stderr, "tex->width      : %d\n", tex->width);
		// 	fprintf(stderr, "tex->height     : %d\n", tex->height);
		// 	fprintf(stderr, "line_height     : %d\n", line_height);
		// 	fprintf(stderr, "tex_step        : %f\n", tex_step);
		// }

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

	// fprintf(stderr, "-- dump sprites --\n");
	// for (int i = 0; i < cub->sprite->num; i++) {
	// 	fprintf(stderr, "sprites[%d].x                %lf\n", i, sprites[i].x);
	// 	fprintf(stderr, "sprites[%d].y                %lf\n", i, sprites[i].y);
	// 	fprintf(stderr, "sprites[%d].dist_from_player %lf\n", i, sprites[i].dist_from_player);
	// 	fprintf(stderr, "sprites[%d].tex          %p\n", i, sprites[i].tex);
	// 	fprintf(stderr, "sprites[%d].tex->width   %d\n", i, sprites[i].tex->width);
	// 	fprintf(stderr, "sprites[%d].tex->height  %d\n", i, sprites[i].tex->height);
	// }

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

	// fprintf(stderr, "-- dump sprites after sort with distance from player --\n");
	// for (int i = 0; i < cub->sprite->num; i++) {
	// 	fprintf(stderr, "sprites[%d].x                %lf\n", i, sprites[i].x);
	// 	fprintf(stderr, "sprites[%d].y                %lf\n", i, sprites[i].y);
	// 	fprintf(stderr, "sprites[%d].dist_from_player %lf\n", i, sprites[i].dist_from_player);
	// 	fprintf(stderr, "sprites[%d].tex          %p\n", i, sprites[i].tex);
	// 	fprintf(stderr, "sprites[%d].tex->width   %d\n", i, sprites[i].tex->width);
	// 	fprintf(stderr, "sprites[%d].tex->height  %d\n", i, sprites[i].tex->height);
	// }

	for (int i = 0; i < cub->sprite->num; i++) {
		// プレイヤーからの相対位置
		double	sp_rpos_x = sprites[i].x - pos_x;
		double	sp_rpos_y = sprites[i].y - pos_y;

		// transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]
		double	inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y);

		// transform camera cordinate
		double	trans_x = inv_det * (dir_y * sp_rpos_x + (-dir_x) * sp_rpos_y);
		double	trans_y = inv_det * ((-plane_y) * sp_rpos_x + plane_x * sp_rpos_y);

		// sprite x on window
		int	sprite_x_on_window = (int)((WIN_W / 2) * (1 + trans_x / trans_y));

		// fprintf(stderr, "-- dump sprite var --\n");
		// fprintf(stderr, "sprites[%d].x            %lf\n", i, sprites[i].x);
		// fprintf(stderr, "sprites[%d].y            %lf\n", i, sprites[i].y);
		// fprintf(stderr, "sprites[%d].tex          %p\n", i, sprites[i].tex);
		// fprintf(stderr, "sprites[%d].tex->width   %d\n", i, sprites[i].tex->width);
		// fprintf(stderr, "sprites[%d].tex->height  %d\n", i, sprites[i].tex->height);
		// fprintf(stderr, "pos_x                    %lf\n", pos_x);
		// fprintf(stderr, "pos_y                    %lf\n", pos_y);
		// fprintf(stderr, "sp_rpos_x                %lf\n", sp_rpos_x);
		// fprintf(stderr, "sp_rpos_y                %lf\n", sp_rpos_y);
		// fprintf(stderr, "plane_x                  %lf\n", plane_x);
		// fprintf(stderr, "plane_y                  %lf\n", plane_y);
		// fprintf(stderr, "dir_y                    %lf\n", dir_y);
		// fprintf(stderr, "dir_x                    %lf\n", dir_x);
		// fprintf(stderr, "inv_det                  %lf\n", inv_det);
		// fprintf(stderr, "trans_x                  %lf\n", trans_x);
		// fprintf(stderr, "trans_y                  %lf\n", trans_y);
		// fprintf(stderr, "trans_x/trans_y          %lf\n", trans_x / trans_y);
		// fprintf(stderr, "sprite_x_on_window       %d\n", sprite_x_on_window);

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

		// calculation frame index
		int frame_index = calc_frame_index(sprites[i].textures->len);

		// loop through every vertical stripe of the sprite on screen
		double	step_sprite_tex_x = ((t_texture *)vec_at(sprites[i].textures, frame_index))->width / (double)sprite_width;
		double	step_sprite_tex_y = ((t_texture *)vec_at(sprites[i].textures, frame_index))->height / (double)sprite_height;

		double	itr_x = 0.0;
		double	itr_y = 0.0;

		// !TODO Should be more simple
		if (-sprite_width / 2 + sprite_x_on_window < 0) {
			itr_x = -(-sprite_width / 2 + sprite_x_on_window); // offset
		}
		if (sprite_x_on_window < 0) {
			itr_x += -sprite_x_on_window;
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
				if (tex_x > ((t_texture *)vec_at(sprites[i].textures, frame_index))->width || tex_y > ((t_texture *)vec_at(sprites[i].textures, frame_index))->height)
					continue ;
				unsigned int color = get_texture_color((t_texture *)vec_at(sprites[i].textures, frame_index), tex_x, tex_y);

				if (color == 0x000000) {
					continue ;
				}
				put_pixel(cub, x, y, color);
			}
			itr_x += step_sprite_tex_x;
		}
	}

	draw_minimap(cub);

	put_image(cub);

	// FPS
	t_time	old = cub->timestamp;
	gettimeofday(&cub->timestamp, NULL);
	double frame_time = (cub->timestamp.tv_usec - old.tv_usec) / 1000000.0;
	// fprintf(stderr, "FPS        = %lf\n", 1 / frame_time);

	usleep(16 * 1000); // 1 / 60 seconds
}

int	main(int argc, char **argv)
{
	t_cub		cub;
	t_config	config;
	t_error		err;

	err = parse_arg(argc, argv, &config);
	if (err != NO_ERR)
	{
		fprintf(stderr, "%d\n", err);
		return (1);
	}

	dump_config(&config); // dump

	cub.window = init_window(WIN_W, WIN_H, "cub3d");
	gettimeofday(&cub.timestamp, NULL);

	err = parse_config(&config, &cub);
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
					has_put = true;
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
		fprintf(stderr, "sprites[%d].x                   %lf\n", i, cub->sprite->sprites[i].x);
		fprintf(stderr, "sprites[%d].y                   %lf\n", i, cub->sprite->sprites[i].y);
		fprintf(stderr, "sprites[%d].dist_from_player    %lf\n", i, cub->sprite->sprites[i].dist_from_player);
		for (int j = 0; j < cub->sprite->sprites[i].textures->len; j++) {
			fprintf(stderr, "sprites[%d].textures[%d]->img    %p\n", i, j, ((t_texture *)vec_at(cub->sprite->sprites[i].textures, j))->img);
			fprintf(stderr, "sprites[%d].textures[%d]->width  %d\n", i, j, ((t_texture *)vec_at(cub->sprite->sprites[i].textures, j))->width);
			fprintf(stderr, "sprites[%d].textures[%d]->height %d\n", i, j, ((t_texture *)vec_at(cub->sprite->sprites[i].textures, j))->height);
		}
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
	for (int i = 0; i < config->sp_texs->len; i++) {
		fprintf(stderr, "sprite texture path : [%s]\n", ((t_sprite_path *)vec_at(config->sp_texs, i))->path);
		fprintf(stderr, "sprite texture group: [%d]\n", ((t_sprite_path *)vec_at(config->sp_texs, i))->group);
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
