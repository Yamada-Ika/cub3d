/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 08:55:56 by iyamada           #+#    #+#             */
/*   Updated: 2021/11/15 03:47:52 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int n, char *base)
{
	if (n == 0)
		return (ft_strdup("0"));
	if (ft_strcmp(base, "0123456789") == 0)
		return (ft_itoa(n));
	return (ft_uitoa_base((unsigned int)n, base));
}
