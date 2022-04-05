#include "cub3d.h"

size_t	count_row(char **strs);
size_t	count_col(char **strs);

void	debug_config(t_config *this);

static t_matrix	*strs_to_map(char **map)
{
	size_t		usr_map_row;
	size_t		usr_map_col;
	t_matrix	*world_map;
	size_t		i;
	size_t		j;

	usr_map_row = count_row(map);
	usr_map_col = count_col(map);
	world_map = mat_new(usr_map_row, usr_map_col);
	i = 0;
	while (i < usr_map_row)
	{
		j = 0;
		while (j < usr_map_col)
		{
			if (ft_strchr("NWSE", map[i][j]))
				world_map->values[i][j] = 0;
			else
				world_map->values[i][j] = map[i][j] - '0';
			++j;
		}
		++i;
	}
	return (world_map);
}

static t_map	*new_map(void)
{
	return ((t_map *)ft_calloc(1, sizeof(t_map)));
}

static t_img	*new_img(void)
{
	return ((t_img *)ft_calloc(1, sizeof(t_img)));
}

static t_texture	*new_tex(void)
{
	return ((t_texture *)ft_calloc(1, sizeof(t_texture)));
}

t_texture	*new_texture(void *mlx, char *file)
{
	t_texture	*tex;

	tex = new_tex();
	if (tex == NULL)
		return (NULL);
	tex->img = new_img();
	if (tex->img == NULL)
		return (NULL);
	tex->img->img = mlx_xpm_file_to_image(mlx, file, &tex->width, &tex->height);
	if (tex->img->img == NULL)
		return (NULL);
	tex->img->addr = mlx_get_data_addr(tex->img->img, &tex->img->bits_per_pixel, &tex->img->line_length, &tex->img->endian);
	return (tex);
}

static void	*get_mlx(t_window *this)
{
	return (this->mlx);
}

int	init_game(t_game *game, t_config *cf)
{
	game->window = init_window(WIN_W, WIN_H, WIN_TITLE); // set_window
	game->player = spawn_player(cf->pos_x + 0.5f, cf->pos_y + 0.5f, cf->dir_x, cf->dir_y); // set_player
	game->map = new_map();
	if (game->map == NULL)
		return (MEM_ERR);
	game->map->map = strs_to_map(cf->map);
	if (game->map->map == NULL)
		return (MEM_ERR);
	game->map->no = new_texture(get_mlx(game->window), cf->no_tex_path);
	if (game->map->no == NULL)
		return (MEM_ERR);
	game->map->so = new_texture(get_mlx(game->window), cf->so_tex_path);
	game->map->we = new_texture(get_mlx(game->window), cf->we_tex_path);
	game->map->ea = new_texture(get_mlx(game->window), cf->ea_tex_path);
	game->map->floor_color = cf->floor_color;
	game->map->ceilling_color = cf->ceilling_color;
	return (NO_ERR);
}
