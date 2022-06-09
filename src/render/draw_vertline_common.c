/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:03:21 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 19:02:10 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static double	calc_texture_iterator(t_raycastvar *lvar, t_cub *cub)
{
	if (-lvar->line_height / 2 + WIN_H / 2 + cub->camera->pitch < 0)
		return (fabs(-lvar->line_height / 2 + WIN_H / 2 + cub->camera->pitch)
			* lvar->tex_step);
	return (0.0);
}

void	draw_vertilcal_line(t_raycastvar *lvar, t_cub *cub)
{
	int				i;
	double			itr_tex_y;
	unsigned int	color;
	int				tex_y;

	i = -1;
	while (++i < lvar->draw_start)
		put_pixel(cub, lvar->x, i, cub->map->ceil);
	itr_tex_y = calc_texture_iterator(lvar, cub);
	i = lvar->draw_start - 1;
	while (++i < lvar->draw_end)
	{
		tex_y = (int)itr_tex_y;
		color = get_texture_color(lvar->tex, lvar->tex_x, tex_y);
		if (lvar->side == EAST || lvar->side == SOUTH)
			color = (color >> 1) & 0b011111110111111101111111;
		put_pixel(cub, lvar->x, i, color);
		itr_tex_y += lvar->tex_step;
	}
	i = lvar->draw_end - 1;
	while (++i < WIN_H)
		put_pixel(cub, lvar->x, i, cub->map->floor);
}
