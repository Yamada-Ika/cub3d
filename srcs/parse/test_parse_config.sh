#!/bin/bash

MAIN=$(cat << EOF
#include <assert.h>
#include <string.h>
#include "mlx_window.h"

int main(void)
{
	printf("strs_to_map test start!\n");
	char	*mp[] = {
		"111",
		"101",
		"111",
		NULL,
	};
	t_matrix *map = strs_to_map(mp);
	assert((int)(map->values[0][0]) == 1);
	assert((int)(map->values[0][1]) == 1);
	assert((int)(map->values[0][2]) == 1);
	assert((int)(map->values[1][0]) == 1);
	assert((int)(map->values[1][1]) == 0);
	assert((int)(map->values[1][2]) == 1);
	assert((int)(map->values[0][0]) == 1);
	assert((int)(map->values[0][1]) == 1);
	assert((int)(map->values[0][2]) == 1);
	printf("strs_to_map test ok!\n");

	// printf("new_texture test start!\n");
	// void	*mlx = mlx_init();
	// void	*win = mlx_new_window(mlx, 500, 500, "new_texture test");
	// int w, h;
	// t_texture	*text = new_texture(mlx, "../../map/test.xpm");
	// mlx_put_image_to_window(mlx, win, text->img->img, 0, 0);
	// mlx_loop(mlx);
	// printf("new_texture test ok!\n");
}
EOF
)

echo "$MAIN" > main.c

gcc main.c parse_config.c -I ../../includes  -I ../../libmat -I ../../minilibx-linux -L ../../minilibx-linux -l mlx_Darwin -L ../../libmat -l mat -I ../../libft -L ../../libft -l ft -L/usr/X11/include/../lib -lmlx -lXext -lX11 -lm

rm a.out main.c
