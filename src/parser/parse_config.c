/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:55 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 02:15:00 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	set_mlx_var(t_cub *cub)
{
	cub->window = init_window(WIN_W, WIN_H, "cub3d");
}

void	set_player_var(t_cub *cub, t_config *config)
{
	cub->player = ft_calloc(1, sizeof(t_player));
	cub->player->pos_x = config->pos_x;
	cub->player->pos_y = config->pos_y;
	cub->player->dir_x = config->dir_x;
	cub->player->dir_y = config->dir_y;
	cub->player->plane_x = config->plane_x;
	cub->player->plane_y = config->plane_y;
}

void	set_color_var(t_cub *cub, t_config *config)
{
	cub->map->floor = config->floor_color;
	cub->map->ceil = config->ceil_color;
}

void	set_camera_var(t_cub *cub)
{
	cub->camera = ft_calloc(1, sizeof(t_camera));
}

void	set_time_var(t_cub *cub)
{
	cub->timestamp = gettimestamp();
}

t_error	parse_config(t_config *config, t_cub *cub)
{
	set_mlx_var(cub);
	set_player_var(cub, config);
	set_map_var(cub, config);
	set_color_var(cub, config);
	set_texture_var(cub, config);
	set_sprite_var(cub, config);
	set_minimap_var(cub);
	set_camera_var(cub);
	set_time_var(cub);
	return (NO_ERR);
}
