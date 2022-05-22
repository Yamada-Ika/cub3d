#include "parse.h"

size_t	count_map_heigth(t_config *config)
{
	size_t	i;
	size_t	h;

	h = 0;
	i = config->seek;
	while (config->cub[i + 1] != NULL)
	{
		i++;
		h++;
	}
	return (h);
}

size_t	count_map_width(t_config *config)
{
	return (ft_strlen(config->cub[config->seek]));
}

void	skip_newline(t_config *config)
{
	char	**file;
	int	i;

	file = config->cub;
	i = config->seek - 1;
	while (file[++i] != NULL)
	{
		if (ft_strcmp(file[i], "") == 0)
			continue ;
		break ;
	}
	config->seek = i + 1;
}

t_error	new_map(t_config *config)
{
	int	i;
	t_cell	**map;

	skip_newline(config);
	config->height = count_map_heigth(config);
	config->width = count_map_width(config);
	config->map = ft_calloc(config->height, sizeof(t_cell *));
	i = -1;
	while (++i < config->height)
	{
		config->map[i] = ft_calloc(config->width, sizeof(t_cell));
	}
	return (NO_ERR);
}

t_error	set_map(t_config *config)
{
	int		i;
	int		flag;
	char	*end;
	t_error	err;

	err = new_map(config);
	if (err != NO_ERR)
		return (err);
	int j;
	int idx = config->seek - 1;
	i = -1;
	while (++i < config->height)
	{
		j = -1;
		while (++j < config->width)
		{
			if (config->cub[idx][j] == 'N')
			{
				// set player info
				config->dir_x = -1;
				config->dir_y = 0;
				config->pos_x = i;
				config->pos_y = j;
				config->plane_x = 0;
				config->plane_y = 0.66;
				config->map[i][j].kind = NONE;
				continue ;
			}
			if (config->cub[idx][j] == 'S')
			{
				// set player info
				config->dir_x = 1;
				config->dir_y = 0;
				config->pos_x = i;
				config->pos_y = j;
				config->plane_x = 0;
				config->plane_y = -0.66;
				config->map[i][j].kind = NONE;
				continue ;
			}
			if (config->cub[idx][j] == 'E')
			{
				// set player info
				config->dir_x = 0;
				config->dir_y = 1;
				config->pos_x = i;
				config->pos_y = j;
				config->plane_x = 0.66;
				config->plane_y = 0;
				config->map[i][j].kind = NONE;
				continue ;
			}
			if (config->cub[idx][j] == 'W')
			{
				// set player info
				config->dir_x = 0;
				config->dir_y = -1;
				config->pos_x = i;
				config->pos_y = j;
				config->plane_x = -0.66;
				config->plane_y = 0;
				config->map[i][j].kind = NONE;;
				continue ;
			}
			if (config->cub[idx][j] == '0')
			{
				config->map[i][j].kind = NONE;
				continue ;
			}
			if (config->cub[idx][j] == '1')
			{
				config->map[i][j].kind = WALL;
				continue ;
			}
			if (config->cub[idx][j] == '|')
			{
				config->map[i][j].kind = DOOR;
				config->map[i][j].door_state = CLOSE;
				config->map[i][j].side = LONGITUDINAL;
				config->map[i][j].timer = 0.0;
				continue ;
			}
			if (config->cub[idx][j] == '-')
			{
				config->map[i][j].kind = DOOR;
				config->map[i][j].door_state = CLOSE;
				config->map[i][j].side = TRANSVERSE;
				config->map[i][j].timer = 0.0;
				continue ;
			}
		}
		idx++;
	}
	return (NO_ERR);
}
