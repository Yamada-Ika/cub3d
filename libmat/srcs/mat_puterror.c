/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_puterror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:02:33 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/14 22:03:14 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static size_t	mat_strlen(const char *str);

void	mat_puterror(const char *msg)
{
	write(2, msg, mat_strlen(msg));
}

static size_t	mat_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0x00)
		++i;
	return (i);
}
