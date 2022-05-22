/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:15 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 02:42:16 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	get_texture_color(const t_texture *tex, const int x, const int y)
{
	return (*(int *)(tex->img->addr + (y * tex->img->line_length + x * (tex->img->bits_per_pixel / 8))));
}

long long	gettimestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000);
}

// void	dump_cub(t_cub *cub)
// {
// 	fprintf(stderr, "-- dump cub head --\n");
// 	fprintf(stderr, "-- camera info --\n");
// 	fprintf(stderr, "pitch %lf\n", cub->camera->pitch);
// 	fprintf(stderr, "-- player info --\n");
// 	fprintf(stderr, "position  (%f, %f)\n", cub->player->pos_x, cub->player->pos_y);
// 	fprintf(stderr, "direction (%f, %f)\n", cub->player->dir_x, cub->player->dir_y);
// 	fprintf(stderr, "plane     (%f, %f)\n", cub->player->plane_x, cub->player->plane_y);
// 	fprintf(stderr, "-- map info --\n");
// 	fprintf(stderr, "heigth %d\n", cub->map->heigth);
// 	fprintf(stderr, "width  %d\n", cub->map->width);
// 	for (int i = 0; i < cub->map->heigth; i++) {
// 		for (int j = 0; j < cub->map->width; j++) {
// 			// sprite
// 			bool	has_put = false;
// 			for (int n = 0; n < cub->sprite->num; n++) {
// 				if (i == (int)cub->sprite->sprites[n].x && j == (int)cub->sprite->sprites[n].y) {
// 					fprintf(stderr, ".");
// 					has_put = true;
// 					break ;
// 				}
// 			}
// 			if (has_put)
// 				continue ;
// 			if (i == (int)(cub->player->pos_x) && j == (int)(cub->player->pos_y))
// 				fprintf(stderr, "P");
// 			else if (cub->map->map[i][j].kind == NONE)
// 				fprintf(stderr, " ");
// 			else if (cub->map->map[i][j].kind == WALL)
// 				fprintf(stderr, "█");
// 			else if (cub->map->map[i][j].kind == DOOR && cub->map->map[i][j].side == LONGITUDINAL && cub->map->map[i][j].door_state == CLOSE)
// 				fprintf(stderr, "|");
// 			else if (cub->map->map[i][j].kind == DOOR && cub->map->map[i][j].side == TRANSVERSE && cub->map->map[i][j].door_state == CLOSE)
// 				fprintf(stderr, "-");
// 			else
// 				fprintf(stderr, " ");
// 			if (j == cub->map->width -1)
// 				fprintf(stderr, "\n");
// 		}
// 	}
// 	fprintf(stderr, "-- color info --\n");
// 	fprintf(stderr, "floor   %x\n", cub->map->floor);
// 	fprintf(stderr, "ceil    %x\n", cub->map->ceil) ;
// 	fprintf(stderr, "-- texture info --\n");
// 	fprintf(stderr, "north side %p\n", cub->map->north);
// 	fprintf(stderr, "width %d, height %d\n", cub->map->north->height, cub->map->north->width);
// 	fprintf(stderr, "south side %p\n", cub->map->south);
// 	fprintf(stderr, "width %d, height %d\n", cub->map->south->height, cub->map->south->width);
// 	fprintf(stderr, "east side  %p\n", cub->map->east);
// 	fprintf(stderr, "width %d, height %d\n", cub->map->east->height, cub->map->east->width);
// 	fprintf(stderr, "west side  %p\n", cub->map->west);
// 	fprintf(stderr, "width %d, height %d\n", cub->map->west->height, cub->map->west->width);
// 	fprintf(stderr, "-- sprite info --\n");
// 	fprintf(stderr, "num %d\n", cub->sprite->num);
// 	for (int i = 0; i < cub->sprite->num; i++) {
// 		fprintf(stderr, "sprites[%d].x                   %lf\n", i, cub->sprite->sprites[i].x);
// 		fprintf(stderr, "sprites[%d].y                   %lf\n", i, cub->sprite->sprites[i].y);
// 		fprintf(stderr, "sprites[%d].dist_from_player    %lf\n", i, cub->sprite->sprites[i].dist_from_player);
// 		fprintf(stderr, "cub->sprite->sprites[%d].textures->len %d\n", i, cub->sprite->sprites[i].textures->len);
// 		for (int j = 0; j < cub->sprite->sprites[i].textures->len; j++) {
// 			fprintf(stderr, "sprites[%d].textures[%d]->img    %p\n", i, j, ((t_texture *)vec_at(cub->sprite->sprites[i].textures, j))->img);
// 			fprintf(stderr, "sprites[%d].textures[%d]->width  %d\n", i, j, ((t_texture *)vec_at(cub->sprite->sprites[i].textures, j))->width);
// 			fprintf(stderr, "sprites[%d].textures[%d]->height %d\n", i, j, ((t_texture *)vec_at(cub->sprite->sprites[i].textures, j))->height);
// 		}
// 	}
// 	fprintf(stderr, "-- dump cub tail --\n");
// }

void	update_timestamp(t_cub *cub)
{
	cub->timestamp = gettimestamp();
}

void	update_doorstate(t_cub *cub)
{
	t_cell	**map;
	t_point	*p;
	double	timespan;
	int		i;

	map = cub->map->map;
	i = -1;
	while (++i < cub->map->door_points->len)
	{
		p = (t_point *)vec_at(cub->map->door_points, i);
		if (map[p->x][p->y].door_state == OPEN
			|| map[p->x][p->y].door_state == CLOSE)
		{
			continue ;
		}
		timespan = (gettimestamp() - cub->timestamp) / 100.0;
		if (map[p->x][p->y].door_state == OPENING) {
			map[p->x][p->y].timer += timespan;
			if (map[p->x][p->y].timer < 0.0) {
				map[p->x][p->y].timer = 0.0;
			}
			if (map[p->x][p->y].timer > 1.0) {
				map[p->x][p->y].timer = 1.0;
				map[p->x][p->y].door_state = OPEN;
			}
		}
		if (map[p->x][p->y].door_state == CLOSING) {
			map[p->x][p->y].timer -= timespan;
			if (map[p->x][p->y].timer > 1.0) {
				map[p->x][p->y].timer = 1.0;
			}
			if (map[p->x][p->y].timer < 0.0) {
				map[p->x][p->y].timer = 0.0;
				map[p->x][p->y].door_state = CLOSE;
			}
		}
	}
}

int	render(t_cub *cub)
{
	draw_walls(cub);
	draw_sprites(cub);
	draw_minimap(cub);
	put_image(cub);
	move_sprites(cub);
	update_doorstate(cub);
	usleep(16 * 1000);
	update_timestamp(cub);
	return (0);
}
