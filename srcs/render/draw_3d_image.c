/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:40:52 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 14:56:37 by kkaneko          ###   ########.fr       */
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
	}
}
