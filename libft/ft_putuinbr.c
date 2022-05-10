/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuinbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 22:21:57 by iyamada           #+#    #+#             */
/*   Updated: 2021/10/29 10:37:14 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putuinbr(unsigned int n)
{
	if (n <= 9)
		ft_putchar(n + '0');
	else
	{
		ft_putuinbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
}
