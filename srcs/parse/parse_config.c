/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:57:07 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/10 17:57:08 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

int	parse_config(t_config *cf)
{
	t_error	err;

	print_progress("parse texture path");
	err = parse_texture_path(cf);
	if (err != NO_ERR)
		return (err);
	print_progress("parse color value");
	err = parse_rgb(cf);
	if (err != NO_ERR)
		return (err);
	print_progress("parse map");
	err = parse_map(cf);
	if (err != NO_ERR)
		return (err);
	print_progress("parse player position");
	err = parse_player_info(cf);
	if (err != NO_ERR)
		return (err);
	return (NO_ERR);
}
