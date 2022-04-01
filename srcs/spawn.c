/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:54:10 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 03:17:36 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	*ft_calloc(size_t nmemb, size_t size);
static void	ft_bzero(void *s, size_t n);

t_player	*spawn_player(double pos_x, double pos_y,
							double dir_x, double dir_y)
{
	t_player	*player;

	player = (t_player *)ft_calloc(1, sizeof(t_player));
	player->pos = mat_affine_new(2);
	player->dir = mat_affine_new(2);
	player->pos->vector = mat_vector_col_2d(pos_x, pos_y);
	player->dir->vector = mat_vector_col_2d(dir_x, dir_y);
	return (player);
}

static void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	res = malloc(size * nmemb);
	if (res == NULL)
		exit_with_error(MALLOC_ERR, 1);
	ft_bzero(res, size * nmemb);
	return (res);
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*uc_s;
	size_t			i;

	uc_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		uc_s[i] = 0;
		++i;
	}
}
