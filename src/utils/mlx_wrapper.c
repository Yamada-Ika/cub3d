#include "cub3d.h"

void	put_pixel(t_cub *cub, int x, int y, unsigned int color)
{
	my_mlx_pixel_put(cub->window->img_front, x, y, color);
}

void	put_image(t_cub *cub)
{
	mlx_put_image_to_window(cub->window->mlx,
						cub->window->mlx_win,
						cub->window->img_front->img,
						0, 0);
}

void	loop(t_cub *cub)
{
	mlx_loop(cub->window->mlx);
}
