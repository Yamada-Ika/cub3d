#include "parse.h"

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

t_error	parse_config(t_config *config, t_cub *cub)
{
	// mlx
	cub->window = init_window(WIN_W, WIN_H, "cub3d");

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
	// ドアの座標を覚えておく
	cub->map->door_points = vec_new(sizeof(t_point));
	for (int x = 0; x < cub->map->heigth; x++) {
		for (int y = 0; y < cub->map->width; y++) {
			if (cub->map->map[x][y].kind == DOOR) {
				t_point	p;
				p.x = x;
				p.y = y;
				vec_push_back(cub->map->door_points, &p);
			}
		}
	}

	// floor and ceil color
	cub->map->floor = config->floor_color;
	cub->map->ceil = config->ceil_color;

	// texture
	cub->map->north = new_texture(cub, config->no_tex_path);
	cub->map->south = new_texture(cub, config->so_tex_path);
	cub->map->east = new_texture(cub, config->ea_tex_path);
	cub->map->west = new_texture(cub, config->we_tex_path);

	// sprite
	cub->sprite = ft_calloc(1, sizeof(t_sprite_info));
	cub->sprite->num = config->sp_num;
	cub->sprite->sprites = ft_calloc(config->sp_num, sizeof(t_sprite));
	cub->sprite->buf_perp = ft_calloc(WIN_W, sizeof(double));

	int seek = 0;
	for (int i = 0; i < config->sp_num; i++) {
		cub->sprite->sprites[i].textures = vec_new(sizeof(t_texture));
		fprintf(stderr, "cub->sprite->sprites[%d].textures : %p\n", i, cub->sprite->sprites[i].textures);
		for (; seek < config->sp_texs; seek++) {
			if (((t_sprite_path *)vec_at(config->sp_texs, seek))->group == i) {
				t_texture *tex = new_texture(cub, ((t_sprite_path *)vec_at(config->sp_texs, seek))->path);

				vec_push_back(cub->sprite->sprites[i].textures, tex);
				continue;
			}
			break;
		}
		sprite_position_generator(cub, &cub->sprite->sprites[i].x, &cub->sprite->sprites[i].y);
	}

	// minimap
	cub->minimap = ft_calloc(1, sizeof(t_minimap_info));
	cub->minimap->height = 240;
	cub->minimap->width = 240;
	cub->minimap->buf = ft_calloc(240, sizeof(unsigned int *));
	for (int i = 0; i < 240; i++) {
		cub->minimap->buf[i] = ft_calloc(240, sizeof(unsigned int));
		for (int j = 0; j < 240; j++) {
			cub->minimap->buf[i][j] = 0xbccddb;
		}
	}

	// camera
	cub->camera = ft_calloc(1, sizeof(t_camera));

	// time
	cub->timestamp = gettimestamp();
	return (NO_ERR);
}

t_error	parse(int argc, char **argv, t_cub *cub)
{
	t_config	config;
	t_error		err;

	err = parse_arg(argc, argv, &config);
	if (err != NO_ERR)
		return (err);
	dump_config(&config); // dump
	return (parse_config(&config, cub));
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
