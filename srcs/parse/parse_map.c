/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:57:13 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/10 17:57:13 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static bool	is_non_closed(t_config *cf, size_t x, size_t y)
{
	return (
		x == 0
		|| x + 1 == cf->map_col_size
		|| y == 0
		|| y + 1 == cf->map_row_size
		|| cf->map[y][x - 1] == ' '
		|| cf->map[y][x + 1] == ' '
		|| cf->map[y - 1][x] == ' '
		|| cf->map[y + 1][x] == ' '
	);
}

int	parse_map(t_config *cf)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < cf->map_row_size)
	{
		x = 0;
		while (x < cf->map_col_size)
		{
			if (cf->map[y][x] == '0'
				|| ft_strchr("NWSE", cf->map[y][x]) != NULL)
			{
				if (is_non_closed(cf, x, y))
					return (NON_CLOSED_MAP);
			}
			x++;
		}
		y++;
	}
	return (NO_ERR);
}
