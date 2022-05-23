/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:32:33 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 19:10:20 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

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
	fprintf(stderr, "keycode %d\n", keycode);
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
		hooks_update_doorstate(cub, keycode);
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
	mlx_hook(win, KeyPress, KeyPressMask, handle_key_hook, cub);
	mlx_loop_hook(mlx, render, cub);
}
