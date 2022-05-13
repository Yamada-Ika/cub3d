#include "mlx.h"
#include "mlx_window.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

int	hoge(int keycode)
{
	if (keycode == ESC)
		exit(0);
}

int main(void)
{
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, 500, 500, "texture");

	int	r = 100;
	int x0 = 200;
	int y0 = 200;

	for (int x = 0; x < r; x++) {
		int y = sqrt(r*r - x*x);
		fprintf(stderr, "(%d, %d)\n", x, y);
		mlx_pixel_put(mlx, win, x + x0, -y + y0, 0xffffff);
		mlx_pixel_put(mlx, win, -x + x0, -y + y0, 0xffffff);
		mlx_pixel_put(mlx, win, x + x0, y + y0, 0xffffff);
		mlx_pixel_put(mlx, win, -x + x0, y + y0, 0xffffff);
	}

	mlx_key_hook(win, hoge, NULL);
	mlx_loop(mlx);
}
