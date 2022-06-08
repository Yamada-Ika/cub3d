/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:27 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/08 20:52:52 by kkaneko          ###   ########.fr       */
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
		return (err);
	parse_config(&config, cub);
	free_config(&config);
	return (NO_ERR);
}
