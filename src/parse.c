#include "parse.h"

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

int	parse_arg(int argc, char **argv, t_config *config)
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

t_error	parse_config(t_config *config, t_cub *cub)
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
		cub->sprite->sprites[i].tex = new_texture(cub, config->sp_texs->data[i]);
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
			cub->minimap->buf[i][j] = 0xffffff;
		}
	}
	return (NO_ERR);
}
