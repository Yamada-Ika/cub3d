/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:17:21 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/31 22:22:33 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx_window.h"

static int	handle_key_hook(int keycode, void *params);
static int	handle_mouse_hook(int button, int x, int y, void *param);
static int	ft_exit(void *params);
void	move_left(t_player *player);

void	set_hooks(t_game *game)
{
	mlx_key_hook(game->window->mlx_win, handle_key_hook, game);
	mlx_mouse_hook(game->window->mlx_win, handle_mouse_hook, game);
	mlx_hook(game->window->mlx_win,
			EV_CROSS_BUTTON,
			(1L << EV_CROSS_BUTTON),
			ft_exit,
			NULL);
}

static int	handle_key_hook(int keycode, void *params)
{
	t_game	*game;

	fprintf(stderr, "keycode : %d\n", keycode);
	game = (t_game *)params;
	if (keycode == ESC)
		ft_exit(NULL);
	if (keycode == A_KEY)
	{
		move_left(game->player);
		clear_window(game->window);
		render(game);
	}
	else if (keycode == L_ARROW);
	{
		//turn_left(game->player);
		clear_window(game->window);
		render(game);
	}
}

static int	handle_mouse_hook(int button, int x, int y, void *param)
{}

static int	ft_exit(void *params)
{
	exit(0);
	return (0);
}
