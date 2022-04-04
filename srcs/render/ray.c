/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:28:58 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/03 20:46:43 by kkaneko          ###   ########.fr       */
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

static void	set_ray(t_ray *this, const t_player *player, size_t idx)
{
	this->angle = get_ray_angle(idx);
	this->dir->vector = mat_rotation_2d_new(this->angle, player->dir->vector);
	this->from = mat_dup(player->pos->vector);// set_cast_pos, set_radiate_pos, set_start_point
	this->index = idx;
}

static double	get_ray_angle(size_t idx)
{
	const double	delta_theta = FOV / RAY_NUM;

	return ((FOV / 2.0) - (delta_theta * (double)idx));
}

static void	init_ray(t_ray *ray)
{
	mat_affine_free(ray->dir);
	ray->index = 0;
	ray->angle = 0;
	ray->v_distance = 0;
}
