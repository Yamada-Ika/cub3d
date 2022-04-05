#include "cub3d.h"

// imgからrgbを取得
int	get_rgb_from_image_at(const t_img *img, const int x, const int y)
{
	return (*(int *)(img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8))));
}
