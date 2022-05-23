/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritevar_set_tex_iter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:07:45 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/24 00:01:41 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int	sprite_tex_width(t_cub *cub, t_spritevar *lvar)
{
	t_sprite	*sps;

	sps = cub->sprite->sprites;
	return (
		((t_texture *)vec_at(
				sps[lvar->idx].textures,
				lvar->frame_index)
		)->width
	);
}

static int	sprite_tex_height(t_cub *cub, t_spritevar *lvar)
{
	t_sprite	*sps;

	sps = cub->sprite->sprites;
	return (
		((t_texture *)vec_at(
				sps[lvar->idx].textures,
				lvar->frame_index)
		)->height
	);
}

void	init_sprite_texture_iterator(t_cub *cub, t_spritevar *lvar)
{
	lvar->step_sprite_tex_x = sprite_tex_width(cub, lvar)
		/ (double)lvar->sprite_width;
	lvar->step_sprite_tex_y = sprite_tex_height(cub, lvar)
		/ (double)lvar->sprite_height;
	lvar->itr_x = 0.0;
	lvar->itr_y = 0.0;
	if (-lvar->sprite_width / 2 + lvar->sprite_x_on_window < 0)
		lvar->itr_x = -(-lvar->sprite_width / 2 + lvar->sprite_x_on_window);
	if (lvar->sprite_x_on_window < 0)
		lvar->itr_x += -lvar->sprite_x_on_window;
}
