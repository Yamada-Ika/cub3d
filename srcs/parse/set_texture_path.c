/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:57:09 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/10 17:57:10 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	set_no_texture_path(t_config *this, const char *line)
{
	size_t	start;

	start = next_nonspace(line);
	this->no_tex_path = remove_char(&line[start], '\n');
}

static void	set_so_texture_path(t_config *this, const char *line)
{
	size_t	start;

	start = next_nonspace(line);
	this->so_tex_path = remove_char(&line[start], '\n');
}

static void	set_we_texture_path(t_config *this, const char *line)
{
	size_t	start;

	start = next_nonspace(line);
	this->we_tex_path = remove_char(&line[start], '\n');
}

static void	set_ea_texture_path(t_config *this, const char *line)
{
	size_t	start;

	start = next_nonspace(line);
	this->ea_tex_path = remove_char(&line[start], '\n');
}

void	set_texture_path(t_config *this, const char *line)
{
	if (start_with(line, "NO"))
	{
		set_no_texture_path(this, &line[2]);
	}
	if (start_with(line, "SO"))
	{
		set_so_texture_path(this, &line[2]);
	}
	if (start_with(line, "WE"))
	{
		set_we_texture_path(this, &line[2]);
	}
	if (start_with(line, "EA"))
	{
		set_ea_texture_path(this, &line[2]);
	}
}
