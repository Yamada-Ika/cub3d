#include "mlx.h"
#include "mlx_window.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

int	hoge(int keycode)
{
	if (keycode == ESC)
		exit(0);
}

int calltime = 0;

typedef struct s_test
{
	void	*mlx;
	void	*win;
}	t_test;

int	fuga(t_test *test)
{
	// mlx_key_hook(test->mlx, hoge, test->win);

	mlx_pixel_put(test->mlx, test->win, calltime, 100, 0xffffff);
	fprintf(stderr, "call fuga %d\n", calltime++);
	usleep(10 * 1000); // wait 10 mili-seconds
}

int main(void)
{
	t_test	test;

	test.mlx = mlx_init();
	test.win = mlx_new_window(test.mlx, 500, 500, "texture");

	mlx_key_hook(test.win, hoge, NULL);
	mlx_loop_hook(test.mlx, fuga, &test);
	mlx_loop(test.mlx);
}
