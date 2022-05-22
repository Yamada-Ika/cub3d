/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:57:27 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 01:57:28 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_error	parse(int argc, char **argv, t_cub *cub)
{
	t_config	config;
	t_error		err;

	err = parse_arg(argc, argv, &config);
	if (err != NO_ERR)
		return (err);
	return (parse_config(&config, cub));
}

// void	dump_config(t_config *config)
// {
// 	fprintf(stderr, "-- dump config head --\n");
// 	for (int i = 0; config->cub[i] != NULL; i++) {
// 		fprintf(stderr, "[%s]\n", config->cub[i]);
// 	}
// 	fprintf(stderr, "north texture path : [%s]\n", config->no_tex_path);
// 	fprintf(stderr, "south texture path : [%s]\n", config->so_tex_path);
// 	fprintf(stderr, "west  texture path : [%s]\n", config->we_tex_path);
// 	fprintf(stderr, "east  texture path : [%s]\n", config->ea_tex_path);
// 	fprintf(stderr, "floor color        : [%x]\n", config->floor_color);
// 	fprintf(stderr, "ceil color         : [%x]\n", config->ceil_color);
// 	fprintf(stderr, "sprite num         : [%lld]\n", config->sp_num);
// 	for (int i = 0; i < config->sp_texs->len; i++) {
// 		fprintf(stderr, "sprite texture path : [%s]\n", ((t_sprite_path *)vec_at(config->sp_texs, i))->path);
// 		fprintf(stderr, "sprite texture group: [%d]\n", ((t_sprite_path *)vec_at(config->sp_texs, i))->group);
// 	}
// 	fprintf(stderr, "player dir_x       : [%f]\n", config->dir_x);
// 	fprintf(stderr, "player dir_y       : [%f]\n", config->dir_y);
// 	fprintf(stderr, "player pos_x       : [%f]\n", config->pos_x);
// 	fprintf(stderr, "player pos_y       : [%f]\n", config->pos_y);
// 	fprintf(stderr, "map height         : [%lld]\n", config->height);
// 	fprintf(stderr, "map width          : [%lld]\n", config->width);
// 	// fprintf(stderr, "-- dump map --\n");
// 	// for (long long i = 0; i < config->height; i++) {
// 	// 	for (long long j = 0; j < config->width; j++) {
// 	// 		fprintf(stderr, "%d", config->map[i][j]);
// 	// 		if (j == config->width - 1)
// 	// 			fprintf(stderr, "\n");
// 	// 	}
// 	// }
// 	fprintf(stderr, "-- dump config tail --\n");
// }
