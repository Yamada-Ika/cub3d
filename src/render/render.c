/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:15 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 20:40:20 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	get_texture_color(const t_texture *tex, const int x, const int y)
{
	return (
		*(int *)(tex->img->addr
		+ (y * tex->img->line_length + x * (tex->img->bits_per_pixel / 8)))
	);
}

long long	gettimestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000);
}

void	update_timestamp(t_cub *cub)
{
	cub->timestamp = gettimestamp();
}

int	render(t_cub *cub)
{
	draw_walls(cub);
	draw_sprites(cub);
	draw_minimap(cub);
	put_image(cub);
	move_sprites(cub);
	update_doorstate(cub);
	usleep(16 * 1000);
	update_timestamp(cub);
	return (0);
}
