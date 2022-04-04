/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_affine_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 03:36:54 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 03:38:14 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

void	mat_affine_free(t_affine **affine)
{
	mat_free((*affine)->vector);
	mat_free((*affine)->transform_mat);
	free(*affine);
	*affine = NULL;
}
