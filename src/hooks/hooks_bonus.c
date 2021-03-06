/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:32:33 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/10 02:25:34 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

int	handle_mouse_hook(int x, int y, void *params);
int	stop(void *params);

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

static void	update_jumpstatus(t_cub *cub)
{
	if (cub->player->jump_state == ON_GROUND)
	{
		cub->player->jump_state = JUMPING;
		cub->player->velocity_z = 5.0;
		cub->player->elevation = 0.0;
		return ;
	}
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
		if (hooks_update_doorstate(cub))
			return (0);
		update_jumpstatus(cub);
		return (0);
	}
	return (0);
}

void	install_event_hooks(t_cub *cub)
{
	void	*mlx;
	void	*win;

	mlx = cub->window->mlx;
	win = cub->window->mlx_win;
	mlx_mouse_hide(mlx, win);
	mlx_hook(win, MotionNotify, (1 << MotionNotify), handle_mouse_hook, cub);
	mlx_hook(win, KeyPress, KeyPressMask, handle_key_hook, cub);
	mlx_hook(win, EV_CROSS_BUTTON, (1L << EV_CROSS_BUTTON), stop, NULL);
	mlx_loop_hook(mlx, render, cub);
}
