/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_new_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:22:37 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/08 15:13:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static size_t	count_map_heigth(t_config *config)
{
	size_t	i;
	size_t	h;

	h = 0;
	i = config->seek;
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

	skip_newline(config);
	config->height = count_map_heigth(config);
	config->width = count_map_width(config);
	config->map = ft_calloc(config->height + 1, sizeof(t_cell *));
	i = 0;
	while (i < config->height)
	{
		config->map[i] = ft_calloc(config->width, sizeof(t_cell));
		i++;
	}
	return (NO_ERR);
}
