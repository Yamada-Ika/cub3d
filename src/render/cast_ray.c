/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:10 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 21:39:51 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	cast_ray(t_raycastvar *lvar, t_cub *cub)
{
	while (true)
	{
		update_rayiterator(lvar);
		if (has_hit_wall(lvar, cub))
			break ;
	}
}
