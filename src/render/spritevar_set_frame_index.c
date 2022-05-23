/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritevar_set_frame_index.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:05:47 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 17:12:44 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static long long	time_in_500ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) / 500);
}

static int	calc_frame_index(int frame_len)
{
	return (time_in_500ms() % frame_len);
}

void	update_frame_index(t_cub *cub, t_spritevar *lvar)
{
	t_sprite	*sprites;

	sprites = cub->sprite->sprites;
	lvar->frame_index = calc_frame_index(sprites[lvar->idx].textures->len);
}
