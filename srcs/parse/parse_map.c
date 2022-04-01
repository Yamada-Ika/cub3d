/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:06:29 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 00:26:41 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_matrix	*gen_world_map(void);
static void	*ft_calloc(size_t size);
static void	ft_bzero(void *s, size_t n);

// int parse(int ac, char **av)
// {
//	return (ac != 2);
// }

/*
bool hax_ext(const char *path, const char *ext)
{
	char	*dot_at;
	size_t	dot_index;

	if (ft_strlen(path) < ft_strlen(ext))
		return (false);
	dot_at = ft_strchr(path, '.');
	if (dot_at == NULL) // does not find
		return (false);
	dot_index = dot_at - path;
	
}
*/

// static int parse_path(const char *path)
// {
// if (!has_ext(path, ".hoge"))
// {
//  return (FAIL);
// }
// }

// t_map	*parse_map(const char *file_path)
// {
// 	t_map	*map_info;
// 
// if (parse_path(file_path) == FAIL)
// {
// return (NULL);
// }
// 	return (map_info);
// }

t_map	*parse_map(const char *map_file)
{
	t_map	*map_info;

	map_info = ft_calloc(sizeof(t_map));
	map_info->map = gen_world_map();
	return (map_info);
}

//debug
static t_matrix	*gen_world_map(void)
{
	const size_t usr_map_row = 6;
	const size_t usr_map_col = 5;
	char	usr_map[6][5] = {{1, 1, 1, 1, 1},
							{1, 0, 0, 0, 1},
							{1, 0, 0, 0, 1},
							{2, 0, 0, 0, 2},
							{1, 0, 0, 0, 1},
							{1, 1, 1, 1, 1}};
	t_matrix	*world_map;
	size_t	i;
	size_t	j;

	world_map = mat_new(usr_map_row, usr_map_col);
	i = 0;
	while (i < usr_map_row)
	{
		j = 0;
		while (j < usr_map_col)
		{
			world_map->values[i][j] = usr_map[i][j];
			++j;
		}
		++i;
	}
	return (world_map);
}

//libft
static void	*ft_calloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (res == NULL)
		exit_with_error(MALLOC_ERR, 1);
	ft_bzero(res, size);
	return (res);
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*uc_s;
	size_t			i;

	uc_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		uc_s[i] = 0;
		++i;
	}
}
