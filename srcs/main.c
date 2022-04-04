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

t_map	*parse(int ac, char **av);
int		validate_map(t_map *map);

int main(int ac, char **av)
{
	t_game		game;

	game.map = parse(ac, av);
	if (game.map == NULL)
	{
		printf("Failed to parse argument\n");
		return (1);
	}
	if (validate_map(game.map) == FAIL)
	{
		printf("Invalid map format\t");
		return (1);
	}
	create_game(&game, av);
	render(&game);
	set_hooks(&game);
	mlx_loop(game.window->mlx);
	return (0);
}

static void	create_game(t_game *game, char **av)
{
	// game->map = parse_map(av[1]);
	game->window = init_window(WIN_W, WIN_H, WIN_TITLE);
	game->player = spawn_player(2, 2, 1, 0);
}

void	render(t_game *game)
{
	double			before;
	double			after;
	t_img			*tmp;

	printf("==== player ====\n");
	printf("pos:(%f, %f)\n", game->player->pos->vector->values[0][0],
								game->player->pos->vector->values[1][0]);
	printf("dir:(%f, %f)\n", game->player->dir->vector->values[0][0],
								game->player->dir->vector->values[1][0]);
	get_3d_image(game);
	tmp = game->window->img_front;
	game->window->img_front = game->window->img_back;
	game->window->img_back = tmp;
	mlx_put_image_to_window(game->window->mlx,
							game->window->mlx_win,
							game->window->img_front->img,
							0, 0);
}
