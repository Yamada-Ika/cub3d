/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:35:48 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 09:57:59 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

void	move_player(t_cub *cub, int keycode)
{
	if (keycode == W_KEY)
		return (move_front(cub));
	if (keycode == S_KEY)
		return (move_back(cub));
	if (keycode == A_KEY)
		return (move_left(cub));
	if (keycode == D_KEY)
		return (move_right(cub));
}

bool	should_move_player(int keycode)
{
	return (
		keycode == W_KEY
		|| keycode == S_KEY
		|| keycode == A_KEY
		|| keycode == D_KEY
	);
}
