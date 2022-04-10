/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:57:33 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/10 17:59:15 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	str_to_rgb(const char *s)
{
	char	*end;
	int		r;
	int		g;
	int		b;

	r = ft_strtoll(s, &end, 10);
	end++;
	g = ft_strtoll(end, &end, 10);
	end++;
	b = ft_strtoll(end, &end, 10);
	return (r << 16 | g << 8 | b);
}

static void	set_floor_color(t_config *this, const char *line)
{
	size_t	start;

	start = next_nonspace(line);
	this->floor_color = str_to_rgb(&line[start]);
}

static void	set_ceil_color(t_config *this, const char *line)
{
	size_t	start;

	start = next_nonspace(line);
	this->ceilling_color = str_to_rgb(&line[start]);
}

void	set_color(t_config *this, const char *line)
{
	if (start_with(line, "F"))
		set_floor_color(this, &line[1]);
	if (start_with(line, "C"))
		set_ceil_color(this, &line[1]);
}
