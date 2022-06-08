/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:26:50 by kkaneko           #+#    #+#             */
/*   Updated: 2022/06/08 21:03:33 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	free_cub(char **cub);
static void	free_paths(t_config *config);

void	free_config(t_config *config)
{
	if (config == NULL)
		return ;	
	free_cub(config->cub);
	free_paths(config);
}

static void	free_cub(char **cub)
{
	size_t	i;

	if (cub == NULL)
		return ;
	i = 0;
	while (cub[i] != NULL)
		free(cub[i++]);
	free(cub);
}

static void	free_paths(t_config *config)
{
	free(config->no_tex_path);
	free(config->so_tex_path);
	free(config->we_tex_path);
	free(config->ea_tex_path);
}
