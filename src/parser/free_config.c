/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:26:50 by kkaneko           #+#    #+#             */
/*   Updated: 2022/06/08 15:18:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	free_cub(char **cub);
static void	free_paths(t_config *config);
static void	free_sp_texs(t_vector *sp_texs);
static void	free_map(t_cell **map);

void	free_config(t_config *config, bool fg_err)
{
	if (config == NULL)
		return ;
	free_cub(config->cub);
	free_paths(config);
	if (fg_err)
	{
		free_sp_texs(config->sp_texs);
		free_map(config->map);
	}
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

static void	free_sp_texs(t_vector *sp_texs)
{
	vec_delete(sp_texs, free);
}

static void	free_map(t_cell **map)
{
	size_t	i;

	if (map == NULL)
		return ;
	i = 0;
	while (map[i] != NULL)
		free(map[i++]);
	free(map);
}
