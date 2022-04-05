#include "cub3d.h"

bool	has_ext(const char *path, const char *ext);

int	parse_texture_path(t_config *cf)
{
	if (!has_ext(cf->no_tex_path, "xpm"))
		return (TEX_FILE_ERR);
	if (!has_ext(cf->so_tex_path, "xpm"))
		return (TEX_FILE_ERR);
	if (!has_ext(cf->we_tex_path, "xpm"))
		return (TEX_FILE_ERR);
	if (!has_ext(cf->ea_tex_path, "xpm"))
		return (TEX_FILE_ERR);
	return (NO_ERR);
}

int	parse_rgb(t_config *cf)
{
	if (0xffffff < cf->floor_color)
		return (INVALID_RGB);
	return (NO_ERR);
}

// mapを1行ずつ読み込む, 0と隣接しているブロックを見て、spaceだとfail（NSWEもあるからビミョい）
int	parse_map(t_config *cf)
{
	size_t	x;
	size_t	y;
	int		size;

	size = 0;
	y = 0;
	while (y < cf->map_row_size)
	{
		x = 0;
		while (x < cf->map_col_size)
		{
			if (cf->map[y][x] == '0')
			{
				if (x == 0)
				{
					fprintf(stderr, "x %zu y %zu %c\n", x, y, cf->map[y][x]);
					return (NON_CLOSED_MAP);
				}
				if (x + 1 == cf->map_col_size)
				{
					fprintf(stderr, "x %zu y %zu %c\n", x, y, cf->map[y][x]);
					return (NON_CLOSED_MAP);
				}
				if (y == 0)
				{
					fprintf(stderr, "x %zu y %zu %c\n", x, y, cf->map[y][x]);
					return (NON_CLOSED_MAP);
				}
				if (y + 1 == cf->map_row_size)
				{
					fprintf(stderr, "x %zu y %zu %c\n", x, y, cf->map[y][x]);
					return (NON_CLOSED_MAP);
				}
				if (cf->map[y][x - 1] == ' ')
				{
					fprintf(stderr, "x %zu y %zu %c\n", x, y, cf->map[y][x]);
					return (NON_CLOSED_MAP);
				}
				if (cf->map[y][x + 1] == ' ')
				{
					fprintf(stderr, "x %zu y %zu %c\n", x, y, cf->map[y][x]);
					return (NON_CLOSED_MAP);
				}
				if (cf->map[y - 1][x] == ' ')
				{
					fprintf(stderr, "x %zu y %zu %c\n", x, y, cf->map[y][x]);
					return (NON_CLOSED_MAP);
				}
				if (cf->map[y + 1][x] == ' ')
				{
					fprintf(stderr, "x %zu y %zu %c\n", x, y, cf->map[y][x]);
					return (NON_CLOSED_MAP);
				}
			}
			x++;
		}
		y++;
	}
	return (NO_ERR);
}

int	parse_player_info(t_config *cf)
{
	size_t	x;
	size_t	y;
	size_t	cnt;

	cnt = 0;
	y = 0;
	while (y < cf->map_row_size)
	{
		x = 0;
		while (x < cf->map_col_size)
		{
			if (ft_strchr("NWSE", cf->map[y][x]))
			{
				cf->pos_x = (float)x;
				cf->pos_y = (float)y;
				if (cf->map[y][x] == 'N')
				{
					cf->dir_x = 0.0f;
					cf->dir_y = -1.0f;
				}
				if (cf->map[y][x] == 'W')
				{
					cf->dir_x = -1.0f;
					cf->dir_y = 0.0f;
				}
				if (cf->map[y][x] == 'S')
				{
					cf->dir_x = 0.0f;
					cf->dir_y = 1.0f;
				}
				if (cf->map[y][x] == 'E')
				{
					cf->dir_x = 1.0f;
					cf->dir_y = 0.0f;
				}
				cnt++;
			}
			x++;
		}
		y++;
	}
	if (cnt != 1)
		return (NON_PLAYER);
	return (NO_ERR);
}

int	parse_config(t_config *cf)
{
	t_error	err;

	err = parse_texture_path(cf);
	if (err != NO_ERR)
		return (err);
	err = parse_rgb(cf);
	if (err != NO_ERR)
		return (err);
	err = parse_map(cf);
	if (err != NO_ERR)
		return (err);
	err = parse_player_info(cf);
	if (err != NO_ERR)
		return (err);
	return (NO_ERR);
}
