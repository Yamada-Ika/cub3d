/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:08:51 by kkaneko           #+#    #+#             */
/*   Updated: 2022/06/10 02:22:33 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "cub3d.h"
# include <X11/X.h>

void	move_player(t_cub *cub, int keycode);
void	move_front(t_cub *cub);
void	move_back(t_cub *cub);
void	move_left(t_cub *cub);
void	move_right(t_cub *cub);
bool	should_move_player(int keycode);
void	rotate_2d(double *a, double *b, double angle);
void	move_viewpoint(t_cub *cub, int keycode);
bool	hooks_update_doorstate(t_cub *cub);

#endif
