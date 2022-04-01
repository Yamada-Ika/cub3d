#include "mlx.h"
#include "mlx_window.h"
#include <stdlib.h>
#include <stdio.h>

static void	ft_bzero(void *s, size_t n);
static void	*ft_calloc(size_t nmemb, size_t size);

t_img	*init_img(t_window *win)
{
	t_img	*img;

	img = (t_img *)ft_calloc(1, sizeof(t_img));
	img->img = mlx_new_image(win->mlx, win->width, win->height);
	img->addr = mlx_get_data_addr(
									img->img,
									&(img->bits_per_pixel),
									&(img->line_length),
									&(img->endian));
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
	res->img = init_img(res);
	return (res);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr +
			(y * img->line_length +
			x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

//libft

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
