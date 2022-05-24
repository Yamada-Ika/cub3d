/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:27 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/25 00:38:31 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_error	parse(int argc, char **argv, t_cub *cub)
{
	t_config	*config;
	t_error		err;

	config = ft_calloc(1, sizeof(t_config));
	err = parse_arg(argc, argv, config);
	if (err != NO_ERR)
		return (err);
	return (parse_config(config, cub));
}
