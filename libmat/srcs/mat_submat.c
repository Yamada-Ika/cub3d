/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_submat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 03:22:04 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/15 03:26:42 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

static void	cal_submat(
				t_matrix *res, t_matrix *src, size_t rm_row, size_t rm_col);

t_matrix	*mat_submat(t_matrix *src, size_t rm_row, size_t rm_col)
{
	t_matrix	*res;

	res = mat_new(src->row - 1, src->col - 1);
	cal_submat(res, src, rm_row, rm_col);
	return (res);
}

static void	cal_submat(
				t_matrix *res, t_matrix *src, size_t rm_row, size_t rm_col)
{
	size_t		src_i;
	size_t		src_j;
	size_t		dst_i;
	size_t		dst_j;

	src_i = 0;
	dst_i = 0;
	while (src_i < src->row)
	{
		src_j = 0;
		dst_j = 0;
		if (src_i != rm_row)
		{
			while (src_j < src->col)
			{
				if (src_j != rm_col)
					res->values[dst_i][dst_j++] = src->values[src_i][src_j];
				++src_j;
			}
			++dst_i;
		}
		++src_i;
	}
}
