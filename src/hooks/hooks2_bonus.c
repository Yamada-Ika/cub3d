/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 02:24:36 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/10 02:24:50 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

int	stop(void *params)
{
	(void)params;
	exit(0);
	return (0);
}
