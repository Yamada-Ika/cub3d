/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_common.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:46:25 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 21:46:39 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	get_texture_color(const t_texture *tex, const int x, const int y)
{
	return (
		*(int *)(tex->img->addr
		+ (y * tex->img->line_length + x * (tex->img->bits_per_pixel / 8)))
	);
}
