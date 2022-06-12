/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_set_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:19:16 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 10:19:24 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	set_player_info_in_north(t_config *config, int i, int j)
{
	config->dir_x = -1;
	config->dir_y = 0;
	config->pos_x = i;
	config->pos_y = j;
	config->plane_x = 0;
	config->plane_y = 0.66;
	config->map[i][j].kind = NONE;
}

void	set_player_info_in_south(t_config *config, int i, int j)
{
	config->dir_x = 1;
	config->dir_y = 0;
	config->pos_x = i;
	config->pos_y = j;
	config->plane_x = 0;
	config->plane_y = -0.66;
	config->map[i][j].kind = NONE;
}

void	set_player_info_in_east(t_config *config, int i, int j)
{
	config->dir_x = 0;
	config->dir_y = 1;
	config->pos_x = i;
	config->pos_y = j;
	config->plane_x = 0.66;
	config->plane_y = 0;
	config->map[i][j].kind = NONE;
}

void	set_player_info_in_west(t_config *config, int i, int j)
{
	config->dir_x = 0;
	config->dir_y = -1;
	config->pos_x = i;
	config->pos_y = j;
	config->plane_x = -0.66;
	config->plane_y = 0;
	config->map[i][j].kind = NONE;
}
