/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:04:30 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/14 15:58:44 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_color.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xff);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xff);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xff);
}

int	get_b(int trgb)
{
	return (trgb & 0xff);
}
