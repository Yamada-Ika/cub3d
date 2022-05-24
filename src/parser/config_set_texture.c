/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_set_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:38:25 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/25 01:18:13 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_error	set_north(t_config *config, char *s, int *flag)
{
	if (*flag >> NORTH_PATH_FLAG & 1)
		return (DUPLICATE_NORTH_TEX_ERR);
	config->no_tex_path = ft_strtrim(&s[2], " ");
	*flag |= 1 << NORTH_PATH_FLAG;
	return (NO_ERR);
}

t_error	set_south(t_config *config, char *s, int *flag)
{
	if (*flag >> SOUTH_PATH_FLAG & 1)
		return (DUPLICATE_SOUTH_TEX_ERR);
	config->so_tex_path = ft_strtrim(&s[2], " ");
	*flag |= 1 << SOUTH_PATH_FLAG;
	return (NO_ERR);
}

t_error	set_west(t_config *config, char *s, int *flag)
{
	if (*flag >> WEST_PATH_FLAG & 1)
		return (DUPLICATE_WEST_TEX_ERR);
	config->we_tex_path = ft_strtrim(&s[2], " ");
	*flag |= 1 << WEST_PATH_FLAG;
	return (NO_ERR);
}

t_error	set_east(t_config *config, char *s, int *flag)
{
	if (*flag >> EAST_PATH_FLAG & 1)
		return (DUPLICATE_EAST_TEX_ERR);
	config->ea_tex_path = ft_strtrim(&s[2], " ");
	*flag |= 1 << EAST_PATH_FLAG;
	return (NO_ERR);
}

t_error	parse_texture_paths(t_config *config, char *s, int *flag)
{
	t_error	err;

	err = NO_ERR;
	if (ft_strncmp(s, "NO ", 3) == 0)
		err = set_north(config, s, flag);
	else if (ft_strncmp(s, "SO ", 3) == 0)
		err = set_south(config, s, flag);
	else if (ft_strncmp(s, "WE ", 3) == 0)
		err = set_west(config, s, flag);
	else if (ft_strncmp(s, "EA ", 3) == 0)
		err = set_east(config, s, flag);
	return (err);
}
