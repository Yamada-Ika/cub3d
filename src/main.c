/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:18 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/11 01:55:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_error	parse(int argc, char **argv, t_cub *cub);
int		render(t_cub *cub);
void	install_event_hooks(t_cub *cub);
void	loop(t_cub *cub);

static void	run(t_cub *cub)
{
	render(cub);
	install_event_hooks(cub);
	loop(cub);
}

int	main(int argc, char **argv)
{
	t_cub		cub;
	t_error		err;

	if (argc != 2)
	{
		ft_putstr_fd(USAGE, STDERR_FILENO);
		return (1);
	}
	err = parse(argc, argv, &cub);
	if (err != NO_ERR)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		exit(1);
	}
	run(&cub);
	return (0);
}
