/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:06:29 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/03 20:44:54 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_matrix	*gen_world_map(void);
static t_matrix	*strs_to_map(char **map);

static bool	has_ext(const char *path, const char *ext)
{
	char	*dot_at;
	size_t	dot_index;

	if (ft_strlen(path) < ft_strlen(ext))
		return (false);
	dot_at = ft_strrchr(path, '.');
	if (dot_at == NULL)
		return (false);
	dot_index = ++dot_at - path;
	if (ft_strcmp(&path[dot_index], ext) != 0)
		return (false);
	return (true);
}

static int	parse_path(const char *path)
{
	if (!has_ext(path, "cub"))
		return (FAIL);
	return (SUCCESS);
}

static int str_to_rgb(const char *s)
{
	char	*end;
	int		r;
	int		g;
	int		b;

	r = ft_strtoll(s, &end, 10);
	end++; // ,があるはず
	g = ft_strtoll(end, &end, 10);
	end++; // ,があるはず
	b = ft_strtoll(end, &end, 10);
	return (r << 16 | g << 8 | b); // convert to rgb
}

static char	*append(char *dst, char *src)
{
	char	*tmp_1;
	char	*tmp_2;
	char	*new;

	tmp_1 = dst;
	tmp_2 = src;
	new = ft_strjoin(dst, src);
	free(tmp_1);
	free(tmp_2);
	return (new);
}

static size_t	count_row(char **strs)
{
	size_t	row;

	row = 0;
	while (strs[row] != NULL)
		row++;
	return (row);
}

static size_t	count_col(char **strs)
{
	return (ft_strlen(strs[0]));
}

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
			world_map->values[i][j] = map[i][j] - '0';
			++j;
		}
		++i;
	}
	return (world_map);
}

static t_map	*read_map(const char *file)
{
	size_t	read_cnt;
	t_map	*map;
	char	*line;
	char	*one_line;
	char	**char_map;
	int	fd;

	one_line = ft_strdup("");
	map = (t_map *)ft_calloc(1, sizeof(t_map));
	read_cnt = 0;
	fd = open(file, O_RDONLY);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		// TODO: とりあえずテクスチャのファイル名を突っ込んでいる
		if (read_cnt == 0)
		{
			if (line[0] == 'N' && line[1] == 'O')
			{
				if (line[2] != '\0')
					map->no_texture = ft_strdup(&line[3]);
			}
		}
		if (read_cnt == 1)
		{
			if (line[0] == 'S' && line[1] == 'O')
			{
				if (line[2] != '\0')
					map->so_texture = ft_strdup(&line[3]);
			}
		}
		if (read_cnt == 2)
		{
			if (line[0] == 'W' && line[1] == 'E')
			{
				if (line[2] != '\0')
					map->we_texture = ft_strdup(&line[3]);
			}
		}
		if (read_cnt == 3)
		{
			if (line[0] == 'E' && line[1] == 'A')
			{
				if (line[2] != '\0')
					map->ea_texture = ft_strdup(&line[3]);
			}
		}
		if (read_cnt == 5)
		{
			if (line[0] == 'F')
				map->floor_color = str_to_rgb(&line[1]);
		}
		if (read_cnt == 6)
		{
			if (line[0] == 'C')
				map->ceilling_color = str_to_rgb(&line[1]);
		}
		if (read_cnt >= 8)
		{
			one_line = append(one_line, line);
			continue;
		}
		free(line);
		read_cnt++;
	}
	char_map = ft_split(one_line, '\n');
	map->map = strs_to_map(char_map);
	close(fd);
	return (map);
}

static bool	validate_arg_num(int ac)
{
	return (ac != 2);
}

t_map	*parse(int ac, char **av)
{
	if (validate_arg_num(ac))
		return (NULL);
	if (parse_path(av[1]) == FAIL)
		return (NULL);
	return (read_map(av[1]));
}

int	validate_map(t_map *map)
{
	return (SUCCESS);
}

// static bool	validate_arg_num(int ac)
// {
// 	return (ac != 2);
// }

// t_map	*parse(int ac, char **av)
// {
// 	if (validate_arg_num(ac))
// 		return (NULL);
// 	if (parse_file_path(av[1]) == FAIL)
// 		return (NULL);
// 	return (read_map(av[1]));
// }

// int	validate_map(t_map *map)
// {
// 	return (SUCCESS);
// }

// // imgからrbgを取得
// int	get_rgb_from_image_at(const t_img *img, const int x, const int y)
// {
// 	return (*(int *)(img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8))));
// }

// #include <assert.h>
// #include <string.h>
// // gcc parse_map.c -I ../../includes  -I ../../libmat -I ../../minilibx-linux -L ../../libmat -l mat && ./a.out
// int	main(void)
// {
// 	printf("has_ext test start!\n");
// 	assert(has_ext("hoge.cub", "cub") == true);
// 	assert(has_ext("hoge.c", "cub") == false);
// 	assert(has_ext("hoge.cu", "cub") == false);
// 	assert(has_ext("cub.cub", "cub") == true);
// 	assert(has_ext("cub.cubcub", "cub") == false);
// 	assert(has_ext(".cub", "cub") == true);
// 	printf("has_ext test ok!\n");

// 	printf("append test start!\n");
// 	char	*tmp1;
// 	char	*tmp2;
// 	char	*tmp3;
// 	tmp1 = ft_strdup("hoge");
// 	tmp2 = ft_strdup("fuga");
// 	tmp3 = append(tmp1, tmp2);
// 	assert(strcmp(tmp3, "hogefuga") == 0);
// 	printf("append test ok!\n");

// 	printf("str_to_rgb test start!\n");
// 	assert(str_to_rgb("0,0,0") == 0);
// 	assert(str_to_rgb("255,255,255") == 0xffffff);
// 	assert(str_to_rgb("255,215,0") == 0xffd700);
// 	assert(str_to_rgb("0,128,0") == 0x008000);
// 	printf("str_to_rgb test ok!\n");

// 	printf("parse_path test start!\n");
// 	assert(parse_path("hoge") == FAIL);
// 	assert(parse_path("hoge.cub") == SUCCESS);
// 	printf("parse_path test ok!\n");

// 	printf("read_map test start!\n");
// 	t_map	*map = read_map("../../map/sample.cub");
// 	assert(strcmp(map->no_texture, "./path_to_the_north_texture"));
// 	assert(strcmp(map->so_texture, "./path_to_the_south_texture"));
// 	assert(strcmp(map->we_texture, "./path_to_the_west_texture"));
// 	assert(strcmp(map->ea_texture, "./path_to_the_east_texture"));
// 	assert(map->floor_color == 0xdc6400);
// 	assert(map->ceilling_color == 0xe11e00);
// 	assert((int)(map->map->values[0][0]) == 1);
// 	assert((int)(map->map->values[0][1]) == 1);
// 	assert((int)(map->map->values[0][2]) == 1);
// 	assert((int)(map->map->values[0][3]) == 1);
// 	assert((int)(map->map->values[0][4]) == 1);
// 	assert((int)(map->map->values[1][0]) == 1);
// 	assert((int)(map->map->values[1][1]) == 0);
// 	assert((int)(map->map->values[1][2]) == 0);
// 	assert((int)(map->map->values[1][3]) == 0);
// 	assert((int)(map->map->values[1][4]) == 1);
// 	assert((int)(map->map->values[2][0]) == 1);
// 	assert((int)(map->map->values[2][1]) == 0);
// 	assert((int)(map->map->values[2][2]) == 0);
// 	assert((int)(map->map->values[2][3]) == 0);
// 	assert((int)(map->map->values[2][4]) == 1);
// 	assert((int)(map->map->values[3][0]) == 2);
// 	assert((int)(map->map->values[3][1]) == 0);
// 	assert((int)(map->map->values[3][2]) == 0);
// 	assert((int)(map->map->values[3][3]) == 0);
// 	assert((int)(map->map->values[3][4]) == 2);
// 	assert((int)(map->map->values[4][0]) == 1);
// 	assert((int)(map->map->values[4][1]) == 0);
// 	assert((int)(map->map->values[4][2]) == 0);
// 	assert((int)(map->map->values[4][3]) == 0);
// 	assert((int)(map->map->values[4][4]) == 1);
// 	assert((int)(map->map->values[5][0]) == 1);
// 	assert((int)(map->map->values[5][1]) == 1);
// 	assert((int)(map->map->values[5][2]) == 1);
// 	assert((int)(map->map->values[5][3]) == 1);
// 	assert((int)(map->map->values[5][4]) == 1);
// 	printf("read_map test end!\n");
// }
