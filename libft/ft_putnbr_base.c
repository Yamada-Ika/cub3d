/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:48:57 by iyamada           #+#    #+#             */
/*   Updated: 2021/10/30 01:11:20 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_helper(unsigned int u_n, char *base, unsigned int radix)
{
	if (u_n <= radix - 1)
	{
		ft_putchar(base[u_n]);
		return ;
	}
	ft_putnbr_base_helper(u_n / radix, base, radix);
	ft_putchar(base[u_n % radix]);
}

void	ft_putnbr_base(int n, char *base)
{
	unsigned int	radix;
	unsigned int	u_n;

	if (n < 0 && ft_strcmp(base, "0123456789") == 0)
	{
		ft_putnbr(n);
		return ;
	}
	radix = ft_strlen(base);
	u_n = (unsigned int)n;
	ft_putnbr_base_helper(u_n, base, radix);
}
