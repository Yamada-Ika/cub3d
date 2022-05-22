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

void	set_mlx_var(t_cub *cub)
{
	cub->window = init_window(WIN_W, WIN_H, "cub3d");
}

void	set_player_var(t_cub *cub, t_config *config)
{
	cub->player = ft_calloc(1, sizeof(t_player));
	cub->player->pos_x = config->pos_x;
	cub->player->pos_y = config->pos_y;
	cub->player->dir_x = config->dir_x;
	cub->player->dir_y = config->dir_y;
	cub->player->plane_x = config->plane_x;
	cub->player->plane_y = config->plane_y;
}

void	set_map_var(t_cub *cub, t_config *config)
{
	int		x;
	int		y;
	t_point	p;

	cub->map = ft_calloc(1, sizeof(t_map));
	cub->map->map = config->map;
	cub->map->width = config->width;
	cub->map->heigth = config->height;
	cub->map->door_points = vec_new(sizeof(t_point));
	x = -1;
	while (++x < cub->map->heigth)
	{
		y = -1;
		while (++y < cub->map->width)
		{
			if (cub->map->map[x][y].kind == DOOR)
			{
				p.x = x;
				p.y = y;
				vec_push_back(cub->map->door_points, &p);
			}
		}
	}
}

void	set_color_var(t_cub *cub, t_config *config)
{
	cub->map->floor = config->floor_color;
	cub->map->ceil = config->ceil_color;
}

void	set_texture_var(t_cub *cub, t_config *config)
{
	cub->map->north = new_texture(cub, config->no_tex_path);
	cub->map->south = new_texture(cub, config->so_tex_path);
	cub->map->east = new_texture(cub, config->ea_tex_path);
	cub->map->west = new_texture(cub, config->we_tex_path);
}

void	set_sprite_var(t_cub *cub, t_config *config)
{
	int			seek;
	int			i;
	t_texture	*tex;

	cub->sprite = ft_calloc(1, sizeof(t_sprite_info));
	cub->sprite->num = config->sp_num;
	cub->sprite->sprites = ft_calloc(config->sp_num, sizeof(t_sprite));
	cub->sprite->buf_perp = ft_calloc(WIN_W, sizeof(double));
	seek = 0;
	i = -1;
	while (++i < config->sp_num)
	{
		cub->sprite->sprites[i].textures = vec_new(sizeof(t_texture));
		while (seek < config->sp_texs->len)
		{
			if (((t_sprite_path *)vec_at(config->sp_texs, seek))->group == i)
			{
				tex = new_texture(cub, ((t_sprite_path *)vec_at(config->sp_texs, seek))->path);
				vec_push_back(cub->sprite->sprites[i].textures, tex);
				seek++;
				continue ;
			}
			break ;
		}
		sprite_position_generator(cub, &cub->sprite->sprites[i].x, &cub->sprite->sprites[i].y);
	}
}

void	set_minimap_var(t_cub *cub)
{
	int	x;
	int	y;

	cub->minimap = ft_calloc(1, sizeof(t_minimap_info));
	cub->minimap->height = 240;
	cub->minimap->width = 240;
	cub->minimap->buf = ft_calloc(240, sizeof(unsigned int *));
	x = -1;
	while (++x < 240)
	{
		cub->minimap->buf[x] = ft_calloc(240, sizeof(unsigned int));
		y = -1;
		while (++y < 240)
			cub->minimap->buf[x][y] = 0xbccddb;
	}
}

void	set_camera_var(t_cub *cub)
{
	cub->camera = ft_calloc(1, sizeof(t_camera));
}

void	set_time_var(t_cub *cub)
{
	cub->timestamp = gettimestamp();
}

t_error	parse_config(t_config *config, t_cub *cub)
{
	set_mlx_var(cub);
	set_player_var(cub, config);
	set_map_var(cub, config);
	set_color_var(cub, config);
	set_texture_var(cub, config);
	set_sprite_var(cub, config);
	set_minimap_var(cub);
	set_camera_var(cub);
	set_time_var(cub);
	return (NO_ERR);
}
