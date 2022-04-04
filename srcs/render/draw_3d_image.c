/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:40:52 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/03 21:26:11 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d_image(t_game *game)
{
	const t_player	*player = game->player;
	t_ray			*ray;
	size_t			ray_i;

	ray = new_ray();
	ray_i = 0;
	while (ray_i < RAY_NUM)
	{
		set_ray(ray, player);
		if (cast_ray(ray, game->map))
		{
			draw_in_window(game->window, ray);
			draw_ray_on_minimap(game->window, ray);
		}
		++ray_i;
	}
}

static int	cast_ray(t_ray *ray, t_map *map)
{
	double	t;

	t = 0;
	while (1)
	{
		
	}
}
