/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:17:21 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/07 02:41:36 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx_window.h"
#include "X11/X.h"

static int	handle_key_hook(int keycode, void *params);
static int	handle_mouse_hook(int button, int x, int y, void *param);
static int	ft_exit(void *params);
void	move_left(t_player *player);
static void	re_render(t_game *game);

static int	test(int x, int y, void *params);

void	set_hooks(t_game *game)
{
	mlx_key_hook(game->window->mlx_win, handle_key_hook, game);
	mlx_mouse_hide(game->window->mlx, game->window->mlx_win);
	mlx_mouse_hook(game->window->mlx_win, handle_mouse_hook, game);
	mlx_hook(game->window->mlx_win,
			EV_CROSS_BUTTON,
			(1L << EV_CROSS_BUTTON),
			ft_exit,
			NULL);
	mlx_hook(game->window->mlx_win,
			6, (1 << MotionNotify), test, game);
	// mlx_hook(game->window->mlx_win,
	// 		2, KeyPressMask, handle_key_hook, game);
}

static int	test(int x, int y, void *params)
{
	static int	prev_x = 0;
	static int	prev_y = 0;
	t_game		*game;
	int			fg_re_render;

	fg_re_render = 0;
	game = (t_game *)params;
	if (x % MOUSE_ROT_INTERVAL == 0)
	{
		if (prev_x - x < 0)
			turn_right(game->player, MOUSE_SENSITIVITY);
		else if (prev_x - x > 0)
			turn_left(game->player, MOUSE_SENSITIVITY);
		fg_re_render = 1;
	}
	if (y % MOUSE_ROT_INTERVAL == 0)
	{
		if (prev_y - y > 0)
			game->player->offset += MOUSE_SENSITIVITY * 100;
		else if (prev_y - y < 0)
			game->player->offset -= MOUSE_SENSITIVITY * 100;
		fg_re_render = 1;
	}
	if (fg_re_render)
		re_render(game);
	prev_x = x;
	prev_y = y;
	//printf("(%d, %d)\n", x, y);
	return (0);
}

static int	handle_key_hook(int keycode, void *params)
{
	t_game	*game;

	//fprintf(stderr, "keycode : %d\n", keycode);
	game = (t_game *)params;
	if (keycode == ESC)
		ft_exit(NULL);
	if (handle_movement(keycode, game)
		|| handle_perspective(keycode, game))
	{
		re_render(game);
	}
}

static void	re_render(t_game *game)
{
	clear_window(game->window);
	render(game);
}

static int	handle_mouse_hook(int button, int x, int y, void *param)
{
	printf("(%d, %d)\n", x, y);
}

static int	ft_exit(void *params)
{
	exit(0);
	return (0);
}
