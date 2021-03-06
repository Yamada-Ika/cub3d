/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:41:34 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 15:10:51 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

bool	should_draw_sprite(t_cub *cub, t_spritevar *lvar, int x)
{
	return (
		lvar->trans_y > 0
		&& (0 <= x && x < WIN_W)
		&& lvar->trans_y < cub->sprite->buf_perp[x]
	);
}
