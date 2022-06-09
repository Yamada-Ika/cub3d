/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:32:33 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/10 02:26:03 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

static bool	should_move_viewpoint(int keycode)
{
	return (
		keycode == R_ARROW
		|| keycode == L_ARROW
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
	return (0);
}

static int	stop(void *params)
{
	(void)params;
	exit(0);
	return (0);
}

void	install_event_hooks(t_cub *cub)
{
	void	*mlx;
	void	*win;

	mlx = cub->window->mlx;
	win = cub->window->mlx_win;
	mlx_hook(win, KeyPress, KeyPressMask, handle_key_hook, cub);
	mlx_hook(win, EV_CROSS_BUTTON, (1L << EV_CROSS_BUTTON), stop, NULL);
	mlx_loop_hook(mlx, render, cub);
}
