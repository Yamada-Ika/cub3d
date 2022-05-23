/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:58:02 by iyamada           #+#    #+#             */
/*   Updated: 2022/05/23 17:35:30 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	calc_dist_from_player_to_sprites(t_cub *cub, t_spritevar *lvar)
{
	t_sprite	*sprites;
	t_player	*player;
	int			i;
	double		rpos_x;
	double		rpos_y;

	sprites = cub->sprite->sprites;
	player = cub->player;
	i = -1;
	while (++i < cub->sprite->num)
	{
		lvar->sp_pos_x = sprites[i].x;
		lvar->sp_pos_y = sprites[i].y;
		rpos_x = lvar->sp_pos_x - player->pos_x;
		rpos_y = lvar->sp_pos_y - player->pos_y;
		sprites[i].dist_from_player = rpos_x * rpos_x + rpos_y * rpos_y;
	}
}

static void	multi_inverse_matrix(t_cub *cub, t_spritevar *lvar)
{
	t_sprite	*sprites;
	t_player	*player;
	double		inv_det;

	sprites = cub->sprite->sprites;
	player = cub->player;
	lvar->sp_rpos_x = sprites[lvar->idx].x - player->pos_x;
	lvar->sp_rpos_y = sprites[lvar->idx].y - player->pos_y;
	inv_det = 1.0
		/ (player->plane_x * player->dir_y - player->dir_x * player->plane_y);
	lvar->trans_x = inv_det
		* (player->dir_y * lvar->sp_rpos_x
			+ (-player->dir_x) * lvar->sp_rpos_y);
	lvar->trans_y = inv_det
		* ((-player->plane_y) * lvar->sp_rpos_x
			+ player->plane_x * lvar->sp_rpos_y);
}

static void	trans_to_camera_cordinate(t_cub *cub, t_spritevar *lvar)
{
	multi_inverse_matrix(cub, lvar);
	lvar->sprite_x_on_window = (int)((WIN_W / 2)
			* (1 + lvar->trans_x / lvar->trans_y));
}

static void	set_sprite_draw_range(t_cub *cub, t_spritevar *lvar)
{
	lvar->sprite_height = abs((int)(WIN_H / lvar->trans_y));
	lvar->draw_start_y = -lvar->sprite_height / 2
		+ WIN_H / 2 + cub->camera->pitch;
	if (lvar->draw_start_y < 0)
		lvar->draw_start_y = 0;
	lvar->draw_end_y = lvar->sprite_height / 2 + WIN_H / 2 + cub->camera->pitch;
	if (lvar->draw_end_y >= WIN_H)
		lvar->draw_end_y = WIN_H - 1;
	lvar->sprite_width = abs((int)(WIN_H / lvar->trans_y));
	lvar->draw_start_x = -lvar->sprite_width / 2 + lvar->sprite_x_on_window;
	if (lvar->draw_start_x < 0)
		lvar->draw_start_x = 0;
	lvar->draw_end_x = lvar->sprite_width / 2 + lvar->sprite_x_on_window;
	if (lvar->draw_end_x >= WIN_W)
		lvar->draw_end_x = WIN_W - 1;
}

void	draw_sprites(t_cub *cub)
{
	t_spritevar	lvar;

	calc_dist_from_player_to_sprites(cub, &lvar);
	sort_sprites(cub, &lvar);
	lvar.idx = -1;
	while (++lvar.idx < cub->sprite->num)
	{
		trans_to_camera_cordinate(cub, &lvar);
		set_sprite_draw_range(cub, &lvar);
		update_frame_index(cub, &lvar);
		init_sprite_texture_iterator(cub, &lvar);
		draw_sprite(cub, &lvar);
	}
}
