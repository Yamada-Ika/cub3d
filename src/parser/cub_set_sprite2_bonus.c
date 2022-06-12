/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_set_sprite2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:13:47 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 22:56:37 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	get_texture_id(t_config *config, int idx)
{
	return (((t_sprite_path *)vec_at(config->sp_texs, idx))->group);
}
