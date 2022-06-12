/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_set_map_common.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:43 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 20:54:34 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	set_map_kind(t_config *config, int i, int j, int kind)
{
	config->map[i][j].kind = kind;
}

t_error	set_map(t_config *config)
{
	int		i;
	int		j;
	int		idx;

	idx = config->seek;
	i = 0;
	while (i < config->height)
	{
		j = 0;
		while (j < config->width)
		{
			if (is_map_symbol(config->cub[idx][j]))
				set_map_(config, i, j, idx);
			else
				return (UNKNOWN_MAP_SYMBOL);
			j++;
		}
		idx++;
		i++;
	}
	return (NO_ERR);
}
