/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:36 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 02:25:26 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_error	get_color(char *s, int *color)
{
	char	*end;

	*color = ft_strtoll(&s[1], &end, 10) << 16;
	if (*end != ',' || (*color >> 16 < 0 && 255 < *color >> 16 < 0))
		return (INVALID_COLOR_VAL_ERR);
	end++;
	*color |= ft_strtoll(end, &end, 10) << 8;
	if (*end != ',' || (*color >> 16 < 0 && 255 < *color >> 16 < 0))
		return (INVALID_COLOR_VAL_ERR);
	end++;
	*color |= ft_strtoll(end, &end, 10);
	if (*end != '\0' || (*color >> 16 < 0 && 255 < *color >> 16 < 0))
		return (INVALID_COLOR_VAL_ERR);
	return (NO_ERR);
}

t_error	set_colors(t_config *config, char *s, int *flag)
{
	t_error	err;

	err = NO_ERR;
	if (ft_strncmp(s, "F", 1) == 0)
	{
		if (*flag >> FLOOR_FLAG & 1)
			return (DUPLICATE_FLOOR_COLOR_ERR);
		err = get_color(&s[1], &config->floor_color);
		*flag |= 1 << FLOOR_FLAG;
	}
	else if (ft_strncmp(s, "C", 1) == 0)
	{
		if (*flag >> CEIL_FLAG & 1)
			return (DUPLICATE_CEIL_COLOR_ERR);
		err = get_color(&s[1], &config->ceil_color);
		*flag |= 1 << CEIL_FLAG;
	}
	return (err);
}

t_error	set_color(t_config *config)
{
	char	**file;
	size_t	i;
	int		flag;
	char	*end;
	t_error	err;

	err = NO_ERR;
	file = config->cub;
	flag = 0;
	i = config->seek - 1;
	while (file[++i] != NULL)
	{
		if (err != NO_ERR)
			return (err);
		if (flag == (1 << FLOOR_FLAG | 1 << CEIL_FLAG))
			break ;
		if (is_color_symbol(file[i]))
		{
			err = set_colors(config, file[i], &flag);
			continue ;
		}
		return (UNKNOWN_SYMBOL);
	}
	config->seek = i + 1;
	return (NO_ERR);
}
