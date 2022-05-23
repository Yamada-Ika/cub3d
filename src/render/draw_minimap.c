/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:34:48 by kkaneko           #+#    #+#             */
/*   Updated: 2022/05/23 19:08:17 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static unsigned int	get_minimap_color(t_cub *cub, int x, int y)
{
	return (cub->minimap->buf[x][y]);
}

static unsigned int	get_player_color(t_cub *cub, int x, int y)
{
	void	*tmp1;
	int		tmp2;
	int		tmp3;

	tmp1 = (void *)cub;
	tmp2 = (int)x;
	tmp3 = (int)y;
	return (0xff0000);
}

static void	draw_circle(t_cub *cub, int r,
	unsigned int (* f(t_cub *, int, int)))
{
	int	x;
	int	y;
	int	from;
	int	to;

	x = -1;
	while (++x < r)
	{
		y = sqrt(r * r - x * x);
		from = -y + MINIMAP_CENTER_Y - 1;
		to = y + MINIMAP_CENTER_Y;
		while (++from < to)
			put_pixel(cub, -x + MINIMAP_CENTER_X,
				from, (*f)(cub, from, -x + MINIMAP_CENTER_X));
		from = -y + MINIMAP_CENTER_Y - 1;
		to = y + MINIMAP_CENTER_Y;
		while (++from < to)
			put_pixel(cub, x + MINIMAP_CENTER_X,
				from, (*f)(cub, from, x + MINIMAP_CENTER_X));
	}
}

void	draw_minimap(t_cub *cub)
{
	fill_minimap_buf(cub);
	draw_circle(cub, MINIMAP_SIZE / 2, get_minimap_color);
	draw_circle(cub, 10, get_player_color);
}
