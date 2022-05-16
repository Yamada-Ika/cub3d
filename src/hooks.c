#include "cub3d.h"
#include <X11/X.h>

static bool	can_move(int keycode, t_cub *cub)
{
	if (keycode == W_KEY) // move forward
	{
		// collide wall ?
		if (cub->map->map[(int)(cub->player->pos_x)][(int)(cub->player->pos_y + cub->player->dir_y * MOVE_STEP)] != 0)
			return (false);
		cub->player->pos_y += cub->player->dir_y * MOVE_STEP;
		if (cub->map->map[(int)(cub->player->pos_x + cub->player->dir_x * MOVE_STEP)][(int)(cub->player->pos_y)] != 0)
			return (false);
		cub->player->pos_x += cub->player->dir_x * MOVE_STEP;
		return (true);
	}
	if (keycode == S_KEY) // move back
	{
		// collide wall ?
		if (cub->map->map[(int)(cub->player->pos_x)][(int)(cub->player->pos_y - cub->player->dir_y * MOVE_STEP)] != 0)
			return (false);
		cub->player->pos_y -= cub->player->dir_y * MOVE_STEP;
		if (cub->map->map[(int)(cub->player->pos_x-cub->player->dir_x * MOVE_STEP)][(int)(cub->player->pos_y)] != 0)
			return (false);
		cub->player->pos_x -= cub->player->dir_x * MOVE_STEP;
		return (true);
	}
	if (keycode == R_ARROW) // see right
	{
		double old_dir_x = cub->player->dir_x;
		cub->player->dir_x = cub->player->dir_x * cos(-ROT_STEP) - cub->player->dir_y * sin(-ROT_STEP);
		cub->player->dir_y = old_dir_x * sin(-ROT_STEP) + cub->player->dir_y * cos(-ROT_STEP);
		double old_plane_x = cub->player->plane_x;
		cub->player->plane_x = cub->player->plane_x * cos(-ROT_STEP) - cub->player->plane_y * sin(-ROT_STEP);
		cub->player->plane_y = old_plane_x * sin(-ROT_STEP) + cub->player->plane_y * cos(-ROT_STEP);
		return (true);
	}
	if (keycode == L_ARROW) // see left
	{
		double old_dir_x = cub->player->dir_x;
		cub->player->dir_x = cub->player->dir_x * cos(ROT_STEP) - cub->player->dir_y * sin(ROT_STEP);
		cub->player->dir_y = old_dir_x * sin(ROT_STEP) + cub->player->dir_y * cos(ROT_STEP);
		double old_plane_x = cub->player->plane_x;
		cub->player->plane_x = cub->player->plane_x * cos(ROT_STEP) - cub->player->plane_y * sin(ROT_STEP);
		cub->player->plane_y = old_plane_x * sin(ROT_STEP) + cub->player->plane_y * cos(ROT_STEP);
		return (true);
	}
	return (false);
}

static int	handle_key_hook(int keycode, void *params)
{
	t_cub	*cub;

	cub = (t_cub *)params;
	if (keycode == ESC)
		exit(0);
	can_move(keycode, cub);
}

void	set_hooks(t_cub *cub)
{
	// mlx_key_hook(cub->window->mlx_win, handle_key_hook, cub);
	mlx_hook(cub->window->mlx_win, KeyPress, KeyPressMask, handle_key_hook, cub);
	mlx_loop_hook(cub->window->mlx, render, cub);
}
