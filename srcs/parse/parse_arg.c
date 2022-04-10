/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:57:26 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/10 18:21:05 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	read_map(t_config *this, const int fd, char *line)
{
	char	*one_line;

	one_line = ft_strdup("");
	if (one_line == NULL)
		return (MEM_ERR);
	one_line = append(one_line, line);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		one_line = append(one_line, line);
		if (one_line == NULL)
			return (MEM_ERR);
	}
	set_map(this, one_line);
	if (this->map == NULL)
		return (MEM_ERR);
	return (NO_ERR);
}

int	read_cub_and_set(t_config *this, int fd)
{
	char	*line;
	t_error	err;

	err = NO_ERR;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] == '\n')
			;
		else if (is_texture_info(line))
			set_texture_path(this, line);
		else if (is_color_info(line))
			set_color(this, line);
		else if (is_sprite_info(line))
			set_sprite(this, line);
		else
		{
			err = read_map(this, fd, line);
			continue ;
		}
		free(line);
	}
	return (err);
}

int	set_config(t_config *this, const char *file)
{
	char	*line;
	int		fd;
	t_error	err;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (CUB_FILE_ERR);
	err = read_cub_and_set(this, fd);
	close(fd);
	return (err);
}

int	parse_arg(t_config *this, int ac, char **av)
{
	t_error	err;

	if (validate_arg_num(ac))
		return (INVALID_ARG_NUM);
	print_progress("parse file");
	err = parse_file_path(av[1]);
	if (err != NO_ERR)
		return (err);
	print_progress("set config");
	err = set_config(this, av[1]);
	if (err != NO_ERR)
		return (err);
	this->map_row_size = count_row(this->map);
	this->map_col_size = count_col(this->map);
	return (NO_ERR);
}
