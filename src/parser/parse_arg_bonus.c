/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:52 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 21:14:31 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static bool	should_read_spritepath(t_config *config)
{
	char	**file;
	size_t	i;

	file = config->cub;
	i = config->seek;
	while (file[i] != NULL)
	{
		if (ft_strcmp(file[i], "") == 0)
			break ;
		if (is_sprite_symbol(file[i]))
			return (true);
		i++;
	}
	return (false);
}

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
	if (should_read_spritepath(config))
	{
		err = parse_sprite_paths(config);
		if (err != NO_ERR)
			return (err);
	}
	err = parse_map(config);
	if (err != NO_ERR)
		return (err);
	return (NO_ERR);
}
