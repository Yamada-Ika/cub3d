/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:02:02 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/31 22:43:57 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx_color.h"

static void	ft_bzero(void *s, size_t n);
static void	*ft_calloc(size_t nmemb, size_t size);
static void	create_black_image(t_img *img);

void	clear_window(t_window *window)
{
	static t_img	*img_all_black = NULL;
	size_t			i;
	size_t			j;

	if (img_all_black == NULL)
	{
		img_all_black = init_img(window);
		create_black_image(img_all_black);
	}
	mlx_put_image_to_window(window->mlx,
							window->mlx_win,
							img_all_black->img,
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

static void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	res = malloc(size * nmemb);
	if (res == NULL)
		exit(1);
	ft_bzero(res, size * nmemb);
	return (res);
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*uc_s;
	size_t			i;

	uc_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		uc_s[i] = 0;
		++i;
	}
}

