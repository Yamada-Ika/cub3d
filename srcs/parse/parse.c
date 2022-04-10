/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:57:23 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/11 00:20:36 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	init_config(t_config *this)
{
	this->sprite_num = 0;
}

int	parse(t_config *cf, int ac, char **av)
{
	t_error	err;

	init_config(cf);
	err = parse_arg(cf, ac, av);
	if (err != NO_ERR)
		return (err);
	print_progress("parse config");
	err = parse_config(cf);
	if (err != NO_ERR)
		return (err);
	return (NO_ERR);
}
