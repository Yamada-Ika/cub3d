/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:00:15 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/11 00:20:12 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	print_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		printf("%s\n", strs[i]);
		i++;
	}
}

void	print_progress(const char *act)
{
	fprintf(stderr, "now %s ...\n", act);
}

void	print_lst(t_list *lst)
{
	while (lst != NULL)
	{
		printf("sprite path :[%s]\n", (char *)lst->content);
		lst = lst->next;
	}
}

void	debug_config(t_config *c)
{
	fprintf(stderr, "\n---- debug_config ----\n");
	fprintf(stderr, "no_tex_path    %s\n", c->no_tex_path);
	fprintf(stderr, "so_tex_path    %s\n", c->so_tex_path);
	fprintf(stderr, "we_tex_path    %s\n", c->we_tex_path);
	fprintf(stderr, "ea_tex_path    %s\n", c->ea_tex_path);
	fprintf(stderr, "floor_color    %d %d %d\n", get_r(c->floor_color),
		get_g(c->floor_color), get_b(c->floor_color));
	fprintf(stderr, "ceilling_color %d %d %d\n", get_r(c->ceilling_color),
		get_g(c->ceilling_color), get_b(c->ceilling_color));
	fprintf(stderr, "map_col_size   %zu\n", c->map_col_size);
	fprintf(stderr, "map_row_size   %zu\n", c->map_row_size);
	print_strs(c->map);
	print_lst(c->sprite_paths);
	fprintf(stderr, "sprite_num     %zu\n", c->sprite_num);
	fprintf(stderr, "pos_x          %f\n", c->pos_x);
	fprintf(stderr, "pos_y          %f\n", c->pos_y);
	fprintf(stderr, "dir_x          %f\n", c->dir_x);
	fprintf(stderr, "dir_y          %f\n", c->dir_y);
	fprintf(stderr, "---- debug_config ----\n");
}

void	debug_game(t_game *g)
{
	size_t	i;

	fprintf(stderr, "\n---- debug_game ----\n");
	fprintf(stderr, "sprite_num     %zu\n", g->map->sprite_num);
	i = 0;
	while (i < g->map->sprite_num)
	{
		fprintf(stderr, "sprite address %p\n", g->map->sprites[i].tex);
		fprintf(stderr, "sprite_x       %f\n", g->map->sprites[i].x);
		fprintf(stderr, "sprite_y       %f\n", g->map->sprites[i].y);
		i++;
	}
	fprintf(stderr, "---- debug_game ----\n");
}

