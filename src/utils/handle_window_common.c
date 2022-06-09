/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:40:26 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 10:42:03 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_window.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	is_out_of_range(int idx, size_t limit);

t_img	*init_img(t_window *win)
{
	t_img	*img;

	img = (t_img *)ft_calloc(1, sizeof(t_img));
	img->img = mlx_new_image(win->mlx, win->width, win->height);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel),
			&(img->line_length), &(img->endian));
	return (img);
}

t_window	*init_window(int width, int height, char *title)
{
	t_window	*res;

	res = (t_window *)ft_calloc(1, sizeof(t_window));
	res->width = width;
	res->height = height;
	res->mlx = mlx_init();
	res->mlx_win = mlx_new_window(res->mlx, width, height, title);
	res->img_back = init_img(res);
	res->img_front = init_img(res);
	return (res);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!is_out_of_range(x, WIN_W) && !is_out_of_range(y, WIN_H))
	{
		dst = img->addr
			+ (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

static int	is_out_of_range(int idx, size_t limit)
{
	if (idx < 0 || (size_t)idx >= limit)
		return (1);
	else
		return (0);
}
