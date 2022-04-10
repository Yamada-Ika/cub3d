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
#include "parse.h"
#include "mlx_window.h"
#include <sys/time.h>

int	init_game(t_game *game, t_config *cf);

static void	start_cub3d(t_game *game)
{
	render(game);
	set_hooks(game);
	mlx_loop(game->window->mlx);
}

void hoge(t_config *cf)
{
	debug_config(cf);
}

void	error(t_error err)
{
	char	*msg;

	if (err == INVALID_ARG_NUM)
		msg = ft_strdup("error: Invalid number of argument\n");
	if (err == INVALID_CUB_FILE)
		msg = ft_strdup("error: Invalid cub file extension\n");
	if (err == CUB_FILE_ERR)
		msg = ft_strdup("error: Can not open cub file\n");
	if (err == MEM_ERR)
		msg = ft_strdup("error: Failed to memory allocate\n");
	if (err == TEX_FILE_ERR)
		msg = ft_strdup("error: Invalid texture file extension\n");
	if (err == INVALID_RGB)
		msg = ft_strdup("error: Invalid color value in texture file\n");
	if (err == NON_CLOSED_MAP)
		msg = ft_strdup("error: Map is not closed\n");
	if (err == NON_PLAYER)
		msg = ft_strdup("error: Player does not exist in map\n");
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}

int main(int ac, char **av)
{
	t_game		game;
	t_config	cf;
	t_error		err;

	err = parse(&cf, ac, av);
	if (err != NO_ERR)
	{
		error(err);
		return (1);
	}
	err = init_game(&game, &cf);
	if (err != NO_ERR)
	{
		error(err);
		return (1);
	}

	debug_config(&cf);
	debug_game(&game);

	start_cub3d(&game);
	return (0);
}

void	render(t_game *game)
{
	double			before;
	double			after;
	t_img			*tmp;

	// printf("==== player ====\n");
	// printf("pos:(%f, %f)\n", game->player->pos->vector->values[0][0],
	// 							game->player->pos->vector->values[1][0]);
	// printf("dir:(%f, %f)\n", game->player->dir->vector->values[0][0],
	// 							game->player->dir->vector->values[1][0]);
	get_3d_image(game);
	tmp = game->window->img_front;
	game->window->img_front = game->window->img_back;
	game->window->img_back = tmp;
	mlx_put_image_to_window(game->window->mlx,
							game->window->mlx_win,
							game->window->img_front->img,
							0, 0);
}
