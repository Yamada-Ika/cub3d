#include "mlx.h"
#include "mlx_window.h"
#include <stdlib.h>
#include <unistd.h>

int	hoge(int keycode)
{
	if (keycode == ESC)
		exit(0);
}

int main(void)
{
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, 500, 500, "texture");
	t_img	*img = calloc(1, sizeof(t_img));
	int	width, height;

	img->img = mlx_xpm_file_to_image(mlx, "./image/east.xpm", &width, &height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);

	mlx_put_image_to_window(mlx, win, img->img, 0, 0);
	mlx_key_hook(win, hoge, win);
	mlx_loop(mlx);
}
