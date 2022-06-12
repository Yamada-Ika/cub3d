/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:15 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 22:41:53 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	mywait(void)
{
	int	i;

	i = 0;
	while (i < 100000)
	{
		i++;
	}
}

int	render(t_cub *cub)
{
	draw_walls(cub);
	put_image(cub);
	mywait();
	return (0);
}
