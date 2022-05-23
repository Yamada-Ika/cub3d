/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_set_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:38:25 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 10:38:42 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_error	set_north(t_config *config, char *s, int *flag)
{
	if (*flag >> NORTH_FLAG & 1)
		return (DUPLICATE_NORTH_TEX_ERR);
	config->no_tex_path = ft_strtrim(&s[2], " ");
	*flag |= 1 << NORTH_FLAG;
	return (NO_ERR);
}

t_error	set_south(t_config *config, char *s, int *flag)
{
	if (*flag >> SOUTH_FLAG & 1)
		return (DUPLICATE_SOUTH_TEX_ERR);
	config->so_tex_path = ft_strtrim(&s[2], " ");
	*flag |= 1 << SOUTH_FLAG;
	return (NO_ERR);
}

t_error	set_west(t_config *config, char *s, int *flag)
{
	if (*flag >> WEST_FLAG & 1)
		return (DUPLICATE_WEST_TEX_ERR);
	config->we_tex_path = ft_strtrim(&s[2], " ");
	*flag |= 1 << WEST_FLAG;
	return (NO_ERR);
}

t_error	set_east(t_config *config, char *s, int *flag)
{
	if (*flag >> EAST_FLAG & 1)
		return (DUPLICATE_EAST_TEX_ERR);
	config->ea_tex_path = ft_strtrim(&s[2], " ");
	*flag |= 1 << EAST_FLAG;
	return (NO_ERR);
}
