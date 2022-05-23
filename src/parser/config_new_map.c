/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_new_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:22:37 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 18:58:49 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static size_t	count_map_heigth(t_config *config)
{
	size_t	i;
	size_t	h;

	h = 0;
	i = config->seek - 1;
	while (config->cub[i] != NULL)
	{
		i++;
		h++;
	}
	return (h);
}

static size_t	count_map_width(t_config *config)
{
	return (ft_strlen(config->cub[config->seek]));
}

t_error	new_map(t_config *config)
{
	int		i;
	t_cell	**map;

	skip_newline(config);
	config->height = count_map_heigth(config);
	config->width = count_map_width(config);
	config->map = ft_calloc(config->height, sizeof(t_cell *));
	i = -1;
	while (++i < config->height)
	{
		config->map[i] = ft_calloc(config->width, sizeof(t_cell));
	}
	return (NO_ERR);
}
