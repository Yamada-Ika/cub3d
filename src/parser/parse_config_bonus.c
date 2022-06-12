/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:55 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 22:39:01 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_error	parse_config(t_config *config, t_cub *cub)
{
	t_error	err;

	set_mlx_var(cub);
	set_player_var(cub, config);
	set_map_var(cub, config);
	set_color_var(cub, config);
	err = set_texture_var(cub, config);
	if (err != NO_ERR)
		return (err);
	err = set_sprite_var(cub, config);
	if (err != NO_ERR)
		return (err);
	set_minimap_var(cub);
	set_camera_var(cub);
	set_time_var(cub);
	return (NO_ERR);
}
