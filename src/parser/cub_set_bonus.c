/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_set_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:21:30 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 19:33:52 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	set_time_var(t_cub *cub)
{
	cub->timestamp = gettimestamp();
}

void	set_minimap_var(t_cub *cub)
{
	int	x;
	int	y;

	cub->minimap = ft_calloc(1, sizeof(t_minimap_info));
	cub->minimap->height = 240;
	cub->minimap->width = 240;
	cub->minimap->buf = ft_calloc(240, sizeof(unsigned int *));
	x = -1;
	while (++x < 240)
	{
		cub->minimap->buf[x] = ft_calloc(240, sizeof(unsigned int));
		y = -1;
		while (++y < 240)
			cub->minimap->buf[x][y] = 0xbccddb;
	}
}
