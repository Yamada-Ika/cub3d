/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:54:10 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 18:20:20 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	*spawn_player(double pos_x, double pos_y,
							double dir_x, double dir_y)
{
	t_player	*player;

	player = (t_player *)ft_calloc(1, sizeof(t_player));
	player->pos = mat_affine_new(2);
	player->dir = mat_affine_new(2);
	player->pos->vector = mat_vector_col_2d(pos_x, pos_y);
	player->dir->vector = mat_vector_col_2d(dir_x, dir_y);
	return (player);
}
