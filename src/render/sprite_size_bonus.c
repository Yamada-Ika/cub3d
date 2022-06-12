/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_size_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:41:25 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 15:11:28 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	get_sprite_width(t_cub *cub, t_spritevar *lvar)
{
	t_sprite	*sprites;

	sprites = cub->sprite->sprites;
	return (
		((t_texture *)vec_at(
				sprites[lvar->idx].textures,
				lvar->frame_index)
		)->width
	);
}

int	get_sprite_height(t_cub *cub, t_spritevar *lvar)
{
	t_sprite	*sprites;

	sprites = cub->sprite->sprites;
	return (
		((t_texture *)vec_at(
				sprites[lvar->idx].textures,
				lvar->frame_index)
		)->height
	);
}
