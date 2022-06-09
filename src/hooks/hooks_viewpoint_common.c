/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_viewpoint_common.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:37:49 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 21:52:37 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

void	rotate_2d(double *a, double *b, double angle)
{
	double	tmp_a;
	double	tmp_b;

	tmp_a = (*a) * cos(angle) + (*b) * sin(angle);
	tmp_b = -(*a) * sin(angle) + (*b) * cos(angle);
	*a = tmp_a;
	*b = tmp_b;
}
