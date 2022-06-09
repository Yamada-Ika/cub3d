/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_set_sprite_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:13:47 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 22:34:46 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	new_sprite(t_cub *cub, t_config *config)
{
	cub->sprite = ft_calloc(1, sizeof(t_sprite_info));
	cub->sprite->num = config->sp_num;
	cub->sprite->sprites = ft_calloc(config->sp_num, sizeof(t_sprite));
	cub->sprite->buf_perp = ft_calloc(WIN_W, sizeof(double));
}

char	*get_texture_path(t_config *config, int idx)
{
	return (((t_sprite_path *)vec_at(config->sp_texs, idx))->path);
}

int	get_texture_id(t_config *config, int idx)
{
	return (((t_sprite_path *)vec_at(config->sp_texs, idx))->group);
}

static void	set_sprite_position(t_cub *cub, int idx)
{
	t_sprite	*sprites;

	sprites = cub->sprite->sprites;
	sprite_pos_generator(cub, &sprites[idx].x, &sprites[idx].y);
}

t_error	set_sprite_var(t_cub *cub, t_config *config)
{
	int			idx;
	int			i;
	t_texture	tex;
	t_error		err;

	new_sprite(cub, config);
	idx = 0;
	i = -1;
	while (++i < config->sp_num)
	{
		cub->sprite->sprites[i].textures = vec_new(sizeof(t_texture));
		while (idx < config->sp_texs->len)
		{
			if (((t_sprite_path *)vec_at(config->sp_texs, idx))->group == i)
			{
				err = init_texture(&tex, cub, get_texture_path(config, idx));
				if (err != NO_ERR)
					return (err);
				vec_push_back(cub->sprite->sprites[i].textures, &tex);
				idx++;
				continue ;
			}
			break ;
		}
		set_sprite_position(cub, i);
	}
	return (NO_ERR);
}
