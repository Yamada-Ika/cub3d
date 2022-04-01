#include "cub3d.h"
#include "mlx_window.h"

static void	Debug_matrix(t_matrix *mtx)
{
	mat_print(mtx);
}

void	move_left(t_player *player)
{
	t_matrix	*left_side_dir;
	t_matrix	*rot_mat;

	// DEBUG
	printf("Debug player->pos\n");
	printf("before \n");
	Debug_matrix(player->pos);
	// DEBUG

	rot_mat = mat_rotation_2d(M_PI_2);
	left_side_dir = mat_mul(rot_mat, player->dir);

	// DEBUG
	printf("Debug left_side_dir\n");
	Debug_matrix(left_side_dir);
	// DEBUG

	left_side_dir->values[0][0] *= MOVE_STEP;
	left_side_dir->values[1][0] *= MOVE_STEP;
	// player->pos = mat_add(player->pos, left_side_dir);
	player->pos->values[0][0] = player->pos->values[0][0]
									+ left_side_dir->values[0][0];
	player->pos->values[1][0] = player->pos->values[1][0]
									+ left_side_dir->values[1][0];
	mat_free(left_side_dir);
	mat_free(rot_mat);

	// DEBUG
	printf("after \n");
	Debug_matrix(player->pos);
	// DEBUG
}
