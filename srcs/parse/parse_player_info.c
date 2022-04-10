/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:57:43 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/10 17:57:43 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	set_player_pos(t_config *cf, double x, double y)
{
	cf->pos_x = x;
	cf->pos_y = y;
}

static void	set_player_dir_(t_config *cf, double x, double y)
{
	cf->dir_x = x;
	cf->dir_y = y;
}

static void	set_player_dir(t_config *cf, size_t x, size_t y)
{
	if (cf->map[y][x] == 'N')
		set_player_dir_(cf, 0.0f, -1.0f);
	if (cf->map[y][x] == 'W')
		set_player_dir_(cf, -1.0f, 0.0f);
	if (cf->map[y][x] == 'S')
		set_player_dir_(cf, 0.0f, 1.0f);
	if (cf->map[y][x] == 'E')
		set_player_dir_(cf, 1.0f, 0.0f);
}

int	parse_player_info(t_config *cf)
{
	size_t	x;
	size_t	y;
	size_t	cnt;

	cnt = 0;
	y = 0;
	while (y < cf->map_row_size)
	{
		x = 0;
		while (x < cf->map_col_size)
		{
			if (ft_strchr("NWSE", cf->map[y][x]))
			{
				set_player_pos(cf, (double)x, (double)y);
				set_player_dir(cf, x, y);
				cnt++;
			}
			x++;
		}
		y++;
	}
	if (cnt != 1)
		return (NON_PLAYER);
	return (NO_ERR);
}
