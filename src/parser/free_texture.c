/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:39:07 by user42            #+#    #+#             */
/*   Updated: 2022/06/09 01:39:47 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_texture(t_window *win, t_texture *tex)
{
	if (tex == NULL
		|| win == NULL
		|| win->mlx == NULL)
		return ;
	mlx_destroy_image(win->mlx, tex->img->img);
	free(tex);
}
