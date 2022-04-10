/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:58:46 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/10 17:58:47 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	destroy_config(t_config *cf)
{
	free(cf->no_tex_path);
	free(cf->so_tex_path);
	free(cf->we_tex_path);
	free(cf->ea_tex_path);
	free_strs(cf->map);
}
