#include "cub3d.h"
#include <X11/X.h>

static bool	can_move(int keycode, t_cub *cub)
{
	if (keycode == W_KEY) // move forward
	{
		// collide wall ?
		if (cub->map->map[(int)(cub->player->pos_x)][(int)(cub->player->pos_y + cub->player->dir_y * MOVE_STEP)].kind != NONE)
			return (false);
		cub->player->pos_y += cub->player->dir_y * MOVE_STEP;
		if (cub->map->map[(int)(cub->player->pos_x + cub->player->dir_x * MOVE_STEP)][(int)(cub->player->pos_y)].kind != NONE)
			return (false);
		cub->player->pos_x += cub->player->dir_x * MOVE_STEP;
		return (true);
	}
	if (keycode == S_KEY) // move back
	{
		// collide wall ?
		if (cub->map->map[(int)(cub->player->pos_x)][(int)(cub->player->pos_y - cub->player->dir_y * MOVE_STEP)].kind != NONE)
			return (false);
		cub->player->pos_y -= cub->player->dir_y * MOVE_STEP;
		if (cub->map->map[(int)(cub->player->pos_x-cub->player->dir_x * MOVE_STEP)][(int)(cub->player->pos_y)].kind != NONE)
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
	t_cell	**map;
	t_player	*player;

	fprintf(stderr, "keycode %d\n", keycode);

	cub = (t_cub *)params;
	map = cub->map->map;
	player = cub->player;

	if (keycode == ESC)
		exit(0);
	can_move(keycode, cub);

	// handle camera pitch
	if (keycode == U_ARROW)
	{
		cub->camera->pitch += 10.0;
		return (0);
	}
	if (keycode == D_ARROW)
	{
		cub->camera->pitch += -10.0;
		return (0);
	}
	if (keycode == SPACE)
	{
		double	pos_x = player->pos_x + player->dir_x * 1.0;
		double	pos_y = player->pos_y + player->dir_y * 1.0;
		// ドアの近くにいるとドアを開閉する
		if (map[(int)pos_x][(int)pos_y].kind == DOOR
			&& map[(int)pos_x][(int)pos_y].door_state == CLOSE)
		{
			map[(int)pos_x][(int)pos_y].door_state = OPENING;
			map[(int)pos_x][(int)pos_y].timer = 0.0f;
			return (0);
		}
		if (map[(int)pos_x][(int)pos_y].kind == DOOR
			&& map[(int)pos_x][(int)pos_y].door_state == OPEN)
		{
			map[(int)pos_x][(int)pos_y].door_state = CLOSING;
			map[(int)pos_x][(int)pos_y].timer = 1.0f;
			return (0);
		}
		return (0);
	}
}

void	set_hooks(t_cub *cub)
{
	// mlx_key_hook(cub->window->mlx_win, handle_key_hook, cub);
	mlx_hook(cub->window->mlx_win, KeyPress, KeyPressMask, handle_key_hook, cub);
	mlx_loop_hook(cub->window->mlx, render, cub);
}
