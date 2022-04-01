/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:44:19 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/31 18:48:2 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx_window.h"
#include <sys/time.h>

static void	create_game(t_game *game, char **av);

int main(int ac, char **av)
{
	t_game		game;

	// if (parse(ac, av) == FAIL)
	// {
	//  perror("Failed to parse argument");
	// 	return (1);
	// }
	// game.map = parse_map(av[1]);
	// if (game.map == NULL)
	// {
	//  perror("Failed to parse map data");
	// 	return (1);
	// }
	//validate_args(ac, av);
	create_game(&game, av);
	render(&game);
	set_hooks(&game);
	mlx_loop(game.window->mlx);
	return (0);
}

static void	create_game(t_game *game, char **av)
{
	game->map = parse_map(av[1]);
	game->window = init_window(WIN_W, WIN_H, WIN_TITLE);
	game->player = spawn_player(2, 2, 1, 0);
}

void	render(t_game *game)
{
	struct timeval val;
	double			before;
	double			after;

	gettimeofday(&val, NULL);
	before = val.tv_usec;
	get_3d_image(game);
	mlx_put_image_to_window(game->window->mlx,
							game->window->mlx_win,
							game->window->img->img,
							0, 0);
	gettimeofday(&val, NULL);
	after = val.tv_usec;
	printf("time:%f\n", after - before);
}
