/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:20:24 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/11 00:16:59 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	set_sprite(t_config *this, const char *line)
{
	t_list	*new;
	size_t	start;
	char	*path;

	path = &line[1];
	start = next_nonspace(path);
	new = ft_lstnew(remove_char(&path[start], '\n'));
	if (this->sprite_num == 0)
		this->sprite_paths = new;
	else
		ft_lstadd_back(&this->sprite_paths, new);
	this->sprite_num++;
}
