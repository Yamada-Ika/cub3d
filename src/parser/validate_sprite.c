/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 01:01:03 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/25 01:13:29 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_error	validate_sprite_paths(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->sp_texs->len)
	{
		if (!has_file_ext(get_texture_path(config, i), ".xpm"))
			return (VALIDATE_SPRITE_TEX_NOT_XPM_ERR);
		if (!can_open(get_texture_path(config, i)))
			return (VALIDATE_SPRITE_TEX_CANT_OPEN_ERR);
		if (is_direcory(get_texture_path(config, i)))
			return (VALIDATE_SPRITE_TEX_IS_DIRECTORY_ERR);
		i++;
	}
	return (NO_ERR);
}

t_error	validate_sprite_id(t_config *config)
{
	int	i;
	int	expect;

	expect = 0;
	i = -1;
	while (++i < config->sp_texs->len)
	{
		if (get_texture_id(config, i) < 0)
			return (VALIDATE_INVALID_SPRITE_ID_ERR);
		if (expect == get_texture_id(config, i))
			continue ;
		if (expect + 1 == get_texture_id(config, i))
		{
			expect++;
			continue ;
		}
		return (VALIDATE_INVALID_SPRITE_ID_ERR);
	}
	return (NO_ERR);
}
