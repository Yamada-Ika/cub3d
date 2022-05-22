/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_sprite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:13:47 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 02:13:55 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	set_sprite_var(t_cub *cub, t_config *config)
{
	int			seek;
	int			i;
	t_texture	*tex;

	cub->sprite = ft_calloc(1, sizeof(t_sprite_info));
	cub->sprite->num = config->sp_num;
	cub->sprite->sprites = ft_calloc(config->sp_num, sizeof(t_sprite));
	cub->sprite->buf_perp = ft_calloc(WIN_W, sizeof(double));
	seek = 0;
	i = -1;
	while (++i < config->sp_num)
	{
		cub->sprite->sprites[i].textures = vec_new(sizeof(t_texture));
		while (seek < config->sp_texs->len)
		{
			if (((t_sprite_path *)vec_at(config->sp_texs, seek))->group == i)
			{
				tex = new_texture(cub, ((t_sprite_path *)vec_at(config->sp_texs, seek))->path);
				vec_push_back(cub->sprite->sprites[i].textures, tex);
				seek++;
				continue ;
			}
			break ;
		}
		sprite_pos_generator(cub, &cub->sprite->sprites[i].x, &cub->sprite->sprites[i].y);
	}
}
