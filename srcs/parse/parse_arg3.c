/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:01:08 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/10 18:18:42 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool	start_with(const char *s, const char *head)
{
	return (ft_strncmp(s, head, ft_strlen(head)) == 0);
}

bool	is_texture_info(const char *s)
{
	return (
		start_with(s, "NO")
		|| start_with(s, "SO")
		|| start_with(s, "WE")
		|| start_with(s, "EA")
	);
}

bool	is_color_info(const char *s)
{
	return (
		start_with(s, "F")
		|| start_with(s, "C")
	);
}

bool	validate_arg_num(int ac)
{
	return (ac != 2);
}

bool	is_sprite_info(const char *s)
{
	return (start_with(s, "S"));
}
