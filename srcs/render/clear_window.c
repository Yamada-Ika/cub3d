/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:02:02 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 18:20:19 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx_color.h"

static void	create_black_image(t_img *img);

void	clear_window(t_window *window)
{
	create_black_image(window->img);
	mlx_put_image_to_window(window->mlx,
						window->mlx_win,
						window->img->img,
						0, 0);
}

static void	create_black_image(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			my_mlx_pixel_put(img, x, y, BLACK);
			++x;
		}
		++y;
	}
}
