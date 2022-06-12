/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:52 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 16:02:53 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	parse_arg(int argc, char **argv, t_config *config)
{
	t_error	err;

	if (argc != 2)
		return (INVALID_ARG_NUM_ERR);
	err = parse_cub(config, argv[1]);
	if (err != NO_ERR)
		return (err);
	err = parse_types(config);
	if (err != NO_ERR)
		return (err);
	skip_newline(config);
	err = parse_map(config);
	if (err != NO_ERR)
		return (err);
	return (NO_ERR);
}
