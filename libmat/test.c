#include "libmat.h"
#include <stdio.h>
#include <math.h>

int	main(void)
{
	t_matrix	*vec_row = mat_vector_col_2d(2, 0);
	t_matrix	*rot_mat = mat_rotation_2d_new(M_PI_2);
	t_affine	dst;

	mat_print(vec_row);
	printf("\n");
	mat_print(rot_mat);
	printf("\n");
	dst.vector = vec_row;
	dst.transform_mat = rot_mat;
	mat_rotation_2d(M_PI_2, &dst);
	mat_print(dst.vector);
	return (0);
}
