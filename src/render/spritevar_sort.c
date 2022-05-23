/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritevar_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:09:07 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/24 00:02:03 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	swap_sprite(t_sprite *lhs, t_sprite *rhs)
{
	t_sprite	tmp;

	tmp.x = lhs->x;
	tmp.y = lhs->y;
	tmp.textures = lhs->textures;
	tmp.dist_from_player = lhs->dist_from_player;
	lhs->x = rhs->x;
	lhs->y = rhs->y;
	lhs->textures = rhs->textures;
	lhs->dist_from_player = rhs->dist_from_player;
	rhs->x = tmp.x;
	rhs->y = tmp.y;
	rhs->textures = tmp.textures;
	rhs->dist_from_player = tmp.dist_from_player;
}

void	sort_sprites(t_cub *cub)
{
	bool		has_swap;
	t_sprite	*sprites;
	int			i;

	sprites = cub->sprite->sprites;
	has_swap = false;
	while (true)
	{
		has_swap = false;
		i = -1;
		while (++i < cub->sprite->num - 1)
		{
			if (sprites[i].dist_from_player < sprites[i + 1].dist_from_player)
			{
				swap_sprite(&sprites[i], &sprites[i + 1]);
				has_swap = true;
			}
		}
		if (!has_swap)
			return ;
	}
}
