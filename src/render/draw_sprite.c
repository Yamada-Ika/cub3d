#include "render.h"

void	swap_sprite(t_sprite *lhs, t_sprite *rhs)
{
	t_sprite	tmp;

	tmp.x = lhs->x;
	tmp.y = lhs->y;
	tmp.textures = lhs->textures;
	tmp.dist_from_player = lhs->dist_from_player;
	lhs->x = rhs->x;
	lhs->y = rhs->y;
	lhs->textures = rhs->textures;
	lhs->dist_from_player = rhs->dist_from_player;
	rhs->x = tmp.x;
	rhs->y = tmp.y;
	rhs->textures = tmp.textures;
	rhs->dist_from_player = tmp.dist_from_player;
}

long long time_in_500ms(void) {
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000) / 500;
}

int	calc_frame_index(int frame_len)
{
	return (time_in_500ms() % frame_len);
}

void	calc_dist_from_player_to_sprites(t_cub *cub, t_spritevar *lvar)
{
	t_sprite	*sprites;
	t_player	*player;
	int	i;

	sprites = cub->sprite->sprites;
	player = cub->player;
	i = -1;
	while (++i < cub->sprite->num)
	{
		lvar->sp_pos_x = sprites[i].x;
		lvar->sp_pos_y = sprites[i].y;
		sprites[i].dist_from_player = (lvar->sp_pos_x - player->pos_x) * (lvar->sp_pos_x - player->pos_x)
			+ (lvar->sp_pos_y - player->pos_y) * (lvar->sp_pos_y - player->pos_y);
	}
}

void	sort_sprites(t_cub *cub, t_spritevar *lvar)
{
	bool	has_swap;
	t_sprite	*sprites;
	int	i;

	sprites = cub->sprite->sprites;
	has_swap = false;
	while (true) {
		has_swap = false;
		i = -1;
		while (++i < cub->sprite->num - 1)
		{
			if (sprites[i].dist_from_player < sprites[i + 1].dist_from_player) {
				swap_sprite(&sprites[i], &sprites[i + 1]);
				has_swap = true;
			}
		}
		if (!has_swap)
			return ;
	}
}

// transform sprite with the inverse camera matrix
// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
// [ planeY   dirY ]                                          [ -planeY  planeX ]
void	trans_to_camera_cordinate(t_cub *cub, t_spritevar *lvar)
{
	t_sprite	*sprites;
	t_player	*player;
	double		inv_det;

	sprites = cub->sprite->sprites;
	player = cub->player;
	lvar->sp_rpos_x = sprites[lvar->idx].x - player->pos_x;
	lvar->sp_rpos_y = sprites[lvar->idx].y - player->pos_y;
	inv_det = 1.0 / (player->plane_x * player->dir_y - player->dir_x * player->plane_y);
	lvar->trans_x = inv_det * (player->dir_y * lvar->sp_rpos_x + (-player->dir_x) * lvar->sp_rpos_y);
	lvar->trans_y = inv_det * ((-player->plane_y) * lvar->sp_rpos_x + player->plane_x * lvar->sp_rpos_y);
	lvar->sprite_x_on_window = (int)((WIN_W / 2) * (1 + lvar->trans_x / lvar->trans_y));
}

void	set_sprite_draw_range(t_cub *cub, t_spritevar *lvar)
{
	lvar->sprite_height = abs((int)(WIN_H / lvar->trans_y));
	lvar->draw_start_y = -lvar->sprite_height / 2 + WIN_H / 2 + cub->camera->pitch;
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

void	init_sprite_texture_iterator(t_cub *cub, t_spritevar *lvar)
{
	t_sprite	*sprites;

	sprites = cub->sprite->sprites;
	lvar->step_sprite_tex_x = ((t_texture *)vec_at(sprites[lvar->idx].textures, lvar->frame_index))->width / (double)lvar->sprite_width;
	lvar->step_sprite_tex_y = ((t_texture *)vec_at(sprites[lvar->idx].textures, lvar->frame_index))->height / (double)lvar->sprite_height;
	lvar->itr_x = 0.0;
	lvar->itr_y = 0.0;
	if (-lvar->sprite_width / 2 + lvar->sprite_x_on_window < 0) {
		lvar->itr_x = -(-lvar->sprite_width / 2 + lvar->sprite_x_on_window); // offset
	}
	if (lvar->sprite_x_on_window < 0) {
		lvar->itr_x += -lvar->sprite_x_on_window;
	}
}

void	draw_sprite(t_cub *cub, t_spritevar *lvar)
{
	t_sprite		*sprites;
	int				x;
	int				y;
	int				tex_x;
	int				tex_y;
	unsigned int	color;

	sprites = cub->sprite->sprites;
	x = lvar->draw_start_x - 1;
	while (++x < lvar->draw_end_x)
	{
		if (lvar->trans_y <= 0 || x < 0 || WIN_W < x || lvar->trans_y >= cub->sprite->buf_perp[x]) {
			lvar->itr_x += lvar->step_sprite_tex_x;
			continue ;
		}
		lvar->itr_y = 0.0;
		y = lvar->draw_start_y - 1;
		while (++y < lvar->draw_end_y)
		{
			tex_x = (int)lvar->itr_x;
			tex_y = (int)lvar->itr_y;
			lvar->itr_y += lvar->step_sprite_tex_y;
			if (tex_x > ((t_texture *)vec_at(sprites[lvar->idx].textures, lvar->frame_index))->width || tex_y > ((t_texture *)vec_at(sprites[lvar->idx].textures, lvar->frame_index))->height)
				continue ;
			color = get_texture_color((t_texture *)vec_at(sprites[lvar->idx].textures, lvar->frame_index), tex_x, tex_y);
			if (color == 0x000000) {
				continue ;
			}
			put_pixel(cub, x, y, color);
		}
		lvar->itr_x += lvar->step_sprite_tex_x;
	}
}

void	draw_sprites(t_cub *cub)
{
	t_sprite	*sprites = cub->sprite->sprites;
	t_player	*player = cub->player;
	t_spritevar	lvar;

	calc_dist_from_player_to_sprites(cub, &lvar);
	sort_sprites(cub, &lvar);
	lvar.idx = -1;
	while (++lvar.idx < cub->sprite->num)
	{
		trans_to_camera_cordinate(cub, &lvar);
		set_sprite_draw_range(cub, &lvar);
		lvar.frame_index = calc_frame_index(sprites[lvar.idx].textures->len);
		init_sprite_texture_iterator(cub, &lvar);
		draw_sprite(cub, &lvar);
	}
}

void	move_sprites(t_cub *cub)
{
	t_sprite	*sprites;
	t_player	*player;
	t_spritevar	lvar;

	sprites = cub->sprite->sprites;
	player = cub->player;
	for (int i = 0; i < cub->sprite->num; i++) {
		if (sprites[i].dist_from_player > 10.0)
			continue;
		lvar.sp_rpos_x = player->pos_x - sprites[i].x;
		lvar.sp_rpos_y = player->pos_y - sprites[i].y;
		lvar.delta_x = lvar.sp_rpos_x * SP_MOVE_STEP;
		lvar.delta_y = lvar.sp_rpos_y * SP_MOVE_STEP;
		if (cub->map->map[(int)(sprites[i].x + lvar.delta_x)][(int)sprites[i].y].kind == NONE)
			sprites[i].x += lvar.delta_x;
		if (cub->map->map[(int)sprites[i].x][(int)(sprites[i].y + lvar.delta_y)].kind == NONE)
			sprites[i].y += lvar.delta_y;
	}
}
