#include "cub3d.h"
#include <X11/X.h>

static void	rotate_2d(double *a, double *b, double angle)
{
	double	tmp_a;
	double	tmp_b;

	tmp_a = (*a) * cos(angle) + (*b) * sin(angle);
	tmp_b = -(*a) * sin(angle) + (*b) * cos(angle);
	*a = tmp_a;
	*b = tmp_b;
}

static bool	is_barricade_in_front_of_player(const t_cub *cub, const double x, const double y)
{
	t_cell	**map;

	map = cub->map->map;
	return (
		map[(int)x][(int)y].kind == WALL
		|| (map[(int)x][(int)y].kind == DOOR && map[(int)x][(int)y].door_state == CLOSE)
	);
}

static void	move_player(t_cub *cub, int keycode)
{
	t_cell		**map;
	t_player	*player;

	map = cub->map->map;
	player = cub->player;
	if (keycode == W_KEY)
	{
		if (is_barricade_in_front_of_player(cub, player->pos_x, player->pos_y + player->dir_y * MOVE_STEP))
			return ;
		player->pos_y += player->dir_y * MOVE_STEP;
		if (is_barricade_in_front_of_player(cub, player->pos_x + player->dir_x * MOVE_STEP, player->pos_y))
			return ;
		player->pos_x += player->dir_x * MOVE_STEP;
		return ;
	}
	if (keycode == S_KEY)
	{
		if (is_barricade_in_front_of_player(cub, player->pos_x, player->pos_y - player->dir_y * MOVE_STEP))
			return ;
		player->pos_y -= player->dir_y * MOVE_STEP;
		if (is_barricade_in_front_of_player(cub, player->pos_x - player->dir_x * MOVE_STEP, player->pos_y))
			return ;
		player->pos_x -= player->dir_x * MOVE_STEP;
		return ;
	}
	if (keycode == A_KEY)
	{
		double ortho_dir_x = player->dir_x;
		double ortho_dir_y = player->dir_y;

		rotate_2d(&ortho_dir_x, &ortho_dir_y, -1.57079632679);
		if (is_barricade_in_front_of_player(cub, player->pos_x + ortho_dir_x * MOVE_STEP, player->pos_y + ortho_dir_y * MOVE_STEP))
			return ;
		player->pos_x += ortho_dir_x * MOVE_STEP;
		player->pos_y += ortho_dir_y * MOVE_STEP;
		return ;
	}
	if (keycode == D_KEY)
	{
		double ortho_dir_x = player->dir_x;
		double ortho_dir_y = player->dir_y;
	
		rotate_2d(&ortho_dir_x, &ortho_dir_y, 1.57079632679);
		if (is_barricade_in_front_of_player(cub, player->pos_x + ortho_dir_x * MOVE_STEP, player->pos_y + ortho_dir_y * MOVE_STEP))
			return ;
		player->pos_x += ortho_dir_x * MOVE_STEP;
		player->pos_y += ortho_dir_y * MOVE_STEP;
		return ;
	}
}

static void	move_viewpoint(t_cub *cub, int keycode)
{
	t_player	*player;

	player = cub->player;
	if (keycode == R_ARROW)
	{
		rotate_2d(&player->dir_x, &player->dir_y, ROT_STEP);
		rotate_2d(&player->plane_x, &player->plane_y, ROT_STEP);
		return ;
	}
	if (keycode == L_ARROW)
	{
		rotate_2d(&player->dir_x, &player->dir_y, -ROT_STEP);
		rotate_2d(&player->plane_x, &player->plane_y, -ROT_STEP);
		return ;
	}
	if (keycode == U_ARROW)
	{
		cub->camera->pitch += 10.0;
		return ;
	}
	if (keycode == D_ARROW)
	{
		cub->camera->pitch += -10.0;
		return ;
	}
}

static void	update_doorstate(t_cub *cub, int keycode)
{
	t_cell	**map;
	t_player	*player;

	map = cub->map->map;
	player = cub->player;
	if (keycode == SPACE)
	{
		double	pos_x = player->pos_x + player->dir_x * 1.0;
		double	pos_y = player->pos_y + player->dir_y * 1.0;

		if (map[(int)pos_x][(int)pos_y].kind == DOOR
			&& map[(int)pos_x][(int)pos_y].door_state == CLOSE)
		{
			map[(int)pos_x][(int)pos_y].door_state = OPENING;
			map[(int)pos_x][(int)pos_y].timer = 0.0f;
			return ;
		}
		if (map[(int)pos_x][(int)pos_y].kind == DOOR
			&& map[(int)pos_x][(int)pos_y].door_state == OPEN)
		{
			map[(int)pos_x][(int)pos_y].door_state = CLOSING;
			map[(int)pos_x][(int)pos_y].timer = 1.0f;
			return ;
		}
		return ;
	}
}

static bool	should_move_player(int keycode)
{
	return (
		keycode == W_KEY
		|| keycode == S_KEY
		|| keycode == A_KEY
		|| keycode == D_KEY
	);
}

static bool	should_move_viewpoint(int keycode)
{
	return (
		keycode == R_ARROW
		|| keycode == L_ARROW
		|| keycode == U_ARROW
		|| keycode == D_ARROW
	);
}

static bool	should_update_doorstate(int keycode)
{
	return (
		keycode == SPACE
	);
}

static int	handle_key_hook(int keycode, void *params)
{
	t_cub	*cub;

	cub = (t_cub *)params;
	if (keycode == ESC)
		exit(0);
	if (should_move_player(keycode))
	{
		move_player(cub, keycode);
		return (0);
	}
	if (should_move_viewpoint(keycode))
	{
		move_viewpoint(cub, keycode);
		return (0);
	}
	if (should_update_doorstate(keycode))
	{
		update_doorstate(cub, keycode);
		return (0);
	}
}

void	install_event_hooks(t_cub *cub)
{
	// mlx_key_hook(cub->window->mlx_win, handle_key_hook, cub);
	mlx_hook(cub->window->mlx_win, KeyPress, KeyPressMask, handle_key_hook, cub);
	mlx_loop_hook(cub->window->mlx, render, cub);
}
