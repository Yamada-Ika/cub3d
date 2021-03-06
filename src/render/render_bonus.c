/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:15 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 15:05:41 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	update_timestamp(t_cub *cub)
{
	cub->timestamp = gettimestamp();
}

static void	update_player_jumpstatus(t_cub *cub)
{
	double	timespan;
	double	delta_z;

	if (cub->player->jump_state == ON_GROUND)
		return ;
	timespan = gettimestamp() - cub->timestamp;
	if (timespan < 0)
		timespan = 10;
	delta_z = timespan * cub->player->velocity_z;
	cub->player->elevation += delta_z;
	cub->player->velocity_z--;
	if (cub->player->elevation < 0.0)
	{
		cub->player->jump_state = ON_GROUND;
		cub->player->elevation = 0.0;
		return ;
	}
	if (cub->player->elevation > ELEVATION_LIMIT)
	{
		cub->player->jump_state = GETTING_OFF;
		return ;
	}
}

int	render(t_cub *cub)
{
	draw_walls(cub);
	draw_sprites(cub);
	draw_minimap(cub);
	put_image(cub);
	move_sprites(cub);
	update_doorstate(cub);
	update_player_jumpstatus(cub);
	update_timestamp(cub);
	usleep(16 * 1000);
	return (0);
}
