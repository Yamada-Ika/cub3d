/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:28:58 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 17:59:30 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_ray	*new_ray(void)
{
	t_ray	*new;

	new = (t_ray *)ft_calloc(1, sizeof(t_ray));
	new->dir = mat_affine_new(2);
	return (new);
}

static void	set_ray(t_ray *this, t_player *player, size_t idx)
{
	const double	delta_theta = FOV / RAY_NUM;

	this->angle = (FOV / 2.0) - (delta_theta * (double)idx);
	this->dir->vector = mat_dup(player->dir->vector);
	mat_rotation_2d(this->angle, this->dir);
	this->from = mat_dup(player->pos->vector);// set_cast_pos, set_radiate_pos, set_start_point
	this->index = idx;
}

static double	get_ray_angle(size_t idx)
{
	const double	delta_theta = FOV / RAY_NUM;

	return ((FOV / 2.0) - (delta_theta * (double)idx));
}
