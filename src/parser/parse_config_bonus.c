/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:55 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/25 00:38:55 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
