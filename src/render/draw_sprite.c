/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:03:18 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 18:54:11 by iyamada          ###   ########.fr       */
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

static void	put_sprite_pixel(t_cub *cub, int x, int y, unsigned int c)
{
	if (c == 0x000000)
		return ;
	put_pixel(cub, x, y, c);
}

static bool	is_out_of_sprite_tex_range(t_cub *cub, t_spritevar *lvar)
{
	t_sprite		*sprites;

	sprites = cub->sprite->sprites;
	return (
		(int)lvar->itr_x > get_sprite_width(cub, lvar)
		|| (int)lvar->itr_y > get_sprite_height(cub, lvar)
	);
}

static t_texture	*get_sprite_texture(t_cub *cub, t_spritevar *lvar)
{
	t_sprite	*sprites;

	sprites = cub->sprite->sprites;
	return (
		(t_texture *)vec_at(sprites[lvar->idx].textures, lvar->frame_index)
	);
}

static unsigned int	get_sprite_color(t_cub *cub, t_spritevar *lvar)
{
	return (
		get_texture_color(
			get_sprite_texture(cub, lvar),
			(int)lvar->itr_x,
			(int)lvar->itr_y)
	);
}

void	draw_sprite(t_cub *cub, t_spritevar *lvar)
{
	t_sprite		*sprites;
	int				x;
	int				y;
	unsigned int	color;

	sprites = cub->sprite->sprites;
	x = lvar->draw_start_x - 1;
	while (++x < lvar->draw_end_x)
	{
		if (should_draw_sprite(cub, lvar, x))
		{
			lvar->itr_y = 0.0;
			y = lvar->draw_start_y - 1;
			while (++y < lvar->draw_end_y)
			{
				lvar->itr_y += lvar->step_sprite_tex_y;
				if (is_out_of_sprite_tex_range(cub, lvar))
					continue ;
				color = get_sprite_color(cub, lvar);
				put_sprite_pixel(cub, x, y, color);
			}
		}
		lvar->itr_x += lvar->step_sprite_tex_x;
	}
}
