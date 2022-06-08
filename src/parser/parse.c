/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:27 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/08 15:19:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_error	parse(int argc, char **argv, t_cub *cub)
{
	t_config	config;
	t_error		err;

	ft_bzero(&config, sizeof(t_config));
	err = parse_arg(argc, argv, &config);
	if (err != NO_ERR)
	{
		free_config(&config, true);
		return (err);
	}
	parse_config(&config, cub);
	free_config(&config, false);
	return (err);
}
