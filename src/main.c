/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:18 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/03 00:32:50 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_error	parse(int argc, char **argv, t_cub *cub);
int		render(t_cub *cub);
void	install_event_hooks(t_cub *cub);
void	loop(t_cub *cub);

// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// __attribute__((destructor))
// void	destructor(void)
// {
// 	char	buf[20];

// 	sprintf(buf, "leaks %d", getpid());
// 	system(buf);
// }

void	run(t_cub *cub)
{
	render(cub);
	install_event_hooks(cub);
	loop(cub);
}

char	*get_error_msg(t_error err)
{
	const char	*kw[] = {
		"Error: Invalid number of arguments\n",
		"Error: Failed to read cub file\n",
		"Error: Unknown symbol in cub file\n",
		"Error: Duplication of north texture\n",
		"Error: Duplication of south texture\n",
		"Error: Duplication of west texture\n",
		"Error: Duplication of east texture\n",
		"Error: Not enough numbers of texture\n",
		"Error: Invalid format of cub file\n",
		"Error: Memory depletion\n",
		"Error: Failed to read texture file\n",
		"Error: Map is not closed\n",
		"Error: Player is not in map\n",
	};

	return ((char *)kw[err - 1]);
}

void	print_error(t_error err)
{
	ft_putstr_fd(get_error_msg(err), STDERR_FILENO);
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
		fprintf(stderr, "error kind %d\n", err);
		return (1);
	}
	run(&cub);
	return (0);
}
