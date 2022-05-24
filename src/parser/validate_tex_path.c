/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tex_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 01:03:44 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/24 07:40:30 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool	has_file_ext(char *path, char *ext)
{
	char	*dot_at;

	dot_at = ft_strrchr(path, '.');
	if (dot_at == NULL)
		return (false);
	return (ft_strcmp(dot_at, ext) == 0);
}

bool	can_open(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

bool	is_direcory(char *path)
{
	int		fd;
	char	buf[10];
	ssize_t	size;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	size = read(fd, buf, 10);
	close(fd);
	return (size == -1);
}

t_error	validate_texture_path(t_config *config)
{
	if (!has_file_ext(config->no_tex_path, ".xpm"))
		return (VALIDATE_NORTH_TEX_NOT_XPM_ERR);
	if (!has_file_ext(config->so_tex_path, ".xpm"))
		return (VALIDATE_SOUTH_TEX_NOT_XPM_ERR);
	if (!has_file_ext(config->we_tex_path, ".xpm"))
		return (VALIDATE_WEST_TEX_NOT_XPM_ERR);
	if (!has_file_ext(config->ea_tex_path, ".xpm"))
		return (VALIDATE_EAST_TEX_NOT_XPM_ERR);
	if (!can_open(config->no_tex_path))
		return (VALIDATE_NORTH_TEX_CANT_OPEN_ERR);
	if (!can_open(config->so_tex_path))
		return (VALIDATE_SOUTH_TEX_CANT_OPEN_ERR);
	if (!can_open(config->we_tex_path))
		return (VALIDATE_WEST_TEX_CANT_OPEN_ERR);
	if (!can_open(config->ea_tex_path))
		return (VALIDATE_EAST_TEX_CANT_OPEN_ERR);
	if (is_direcory(config->no_tex_path))
		return (VALIDATE_NORTH_TEX_IS_DIRECTORY_ERR);
	if (is_direcory(config->so_tex_path))
		return (VALIDATE_SOUTH_TEX_IS_DIRECTORY_ERR);
	if (is_direcory(config->we_tex_path))
		return (VALIDATE_WEST_TEX_IS_DIRECTORY_ERR);
	if (is_direcory(config->ea_tex_path))
		return (VALIDATE_EAST_TEX_IS_DIRECTORY_ERR);
	return (NO_ERR);
}
