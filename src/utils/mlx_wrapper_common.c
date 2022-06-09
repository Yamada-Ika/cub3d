/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:32:10 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 02:32:10 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_cub *cub, int x, int y, unsigned int color)
{
	my_mlx_pixel_put(cub->window->img_front, x, y, color);
}

void	put_image(t_cub *cub)
{
	void	*mlx;
	void	*win;
	void	*img;

	mlx = cub->window->mlx;
	win = cub->window->mlx_win;
	img = cub->window->img_front->img;
	mlx_put_image_to_window(mlx, win, img, 0, 0);
}

void	loop(t_cub *cub)
{
	mlx_loop(cub->window->mlx);
}
