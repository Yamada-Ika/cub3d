/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:39:07 by user42            #+#    #+#             */
/*   Updated: 2022/06/08 17:57:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    free_texture(t_window *win, t_texture *tex)
{
    if (tex == NULL
        || win == NULL
        || win->mlx == NULL)
        return ;
    mlx_destroy_image(win->mlx, tex->img->img);
    free(tex);
}
