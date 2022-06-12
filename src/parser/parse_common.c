/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:27 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 22:13:15 by iyamada          ###   ########.fr       */
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
	err = parse_config(&config, cub);
	free_config(&config, false);
	return (err);
}
