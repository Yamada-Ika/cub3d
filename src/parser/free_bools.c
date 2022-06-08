/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:11:30 by kkaneko           #+#    #+#             */
/*   Updated: 2022/06/08 20:56:47 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

void	free_bools(bool **p)
{
	size_t	i;

	if (p == NULL)
		return ;
	i = 0;
	while (p[i] != NULL)
		free(p[i++]);
	free(p);
}
