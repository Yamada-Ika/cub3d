/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:36 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/25 01:23:14 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_error	get_color(char *s, int *color)
{
	char	*end;

	*color = ft_strtoll(&s[1], &end, 10) << 16;
	if (*end != ',' || ((*color >> 16) < 0 && 255 < (*color >> 16)))
		return (INVALID_COLOR_VAL_ERR);
	end++;
	*color |= ft_strtoll(end, &end, 10) << 8;
	if (*end != ',' || ((*color >> 16) < 0 && 255 < (*color >> 16)))
		return (INVALID_COLOR_VAL_ERR);
	end++;
	*color |= ft_strtoll(end, &end, 10);
	if (*end != '\0' || ((*color >> 16) < 0 && 255 < (*color >> 16)))
		return (INVALID_COLOR_VAL_ERR);
	return (NO_ERR);
}

t_error	parse_colors(t_config *config, char *s, int *flag)
{
	t_error	err;

	err = NO_ERR;
	if (ft_strncmp(s, "F ", 2) == 0)
	{
		if (*flag >> FLOOR_COLOR_FLAG & 1)
			return (DUPLICATE_FLOOR_COLOR_ERR);
		err = get_color(&s[1], &config->floor_color);
		*flag |= 1 << FLOOR_COLOR_FLAG;
	}
	else if (ft_strncmp(s, "C ", 2) == 0)
	{
		if (*flag >> CEIL_COLOR_FLAG & 1)
			return (DUPLICATE_CEIL_COLOR_ERR);
		err = get_color(&s[1], &config->ceil_color);
		*flag |= 1 << CEIL_COLOR_FLAG;
	}
	return (err);
}
