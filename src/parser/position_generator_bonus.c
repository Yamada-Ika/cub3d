/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_generator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:58 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 02:30:21 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static long long	g_seed;

static long long	mytime(void)
{
	long long			res;
	char				*end;
	static long long	cnt = 0;

	res = ft_strtoll(__TIME__, &end, 10);
	end++;
	res += ft_strtoll(end, &end, 10);
	end++;
	res += ft_strtoll(end, &end, 10);
	cnt++;
	return (res * cnt);
}

static double	random_generator(void)
{
	g_seed = (A * g_seed + B) % M;
	return ((double)(g_seed + 1.0) / (M + 1.0));
}

void	sprite_pos_generator(t_cub *cub, double *x, double *y)
{
	double	cand_x;
	double	cand_y;

	g_seed = mytime();
	while (true)
	{
		cand_x = random_generator() * (cub->map->heigth - 1);
		cand_y = random_generator() * (cub->map->width - 1);
		if (cub->map->map[(int)cand_x][(int)cand_y].kind != NONE)
			continue ;
		*x = cand_x;
		*y = cand_y;
		break ;
	}
}
