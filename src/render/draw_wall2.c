/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:07 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 16:29:04 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	set_ray_dirction(t_raycastvar *lvar, t_cub *cub)
{
	t_player	*player;

	player = cub->player;
	lvar->camera_x = 2 * lvar->x / (double)WIN_W - 1;
	lvar->ray_dir_x = player->dir_x + player->plane_x * lvar->camera_x;
	lvar->ray_dir_y = player->dir_y + player->plane_y * lvar->camera_x;
}
