/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmat.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:28:01 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/03 21:39:32 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMAT_H
# define LIBMAT_H
# define MALLOC_ERR "Memory allocation error\n"
# define MAT_ADD_ERR "Matrix add failed\n"
# define MAT_MUL_ERR "Matrix mul failed\n"
# define MAT_NOT_REGULAR "The matrix is not regular\n"
# include <stdlib.h>

typedef struct s_matrix
{
	double	**values;
	size_t	row;
	size_t	col;
}			t_matrix;

typedef t_matrix t_vector;

typedef struct s_affine
{
	t_matrix	*vector;
	t_matrix	*transform_mat;
}				t_affine;

/* normal */
void		mat_puterror(const char *msg);
void		mat_free(t_matrix *mat);
t_matrix	*mat_new(size_t row, size_t col);
t_matrix	*mat_add_new(t_matrix *a, t_matrix *b);
void		mat_add(t_matrix *a, t_matrix *b);
t_matrix	*mat_mul_scalar_new(double k, t_matrix *a);
void		mat_mul_scalar(double k, t_matrix *a);
t_matrix	*mat_mul_new(t_matrix *a, t_matrix *b);
void		mat_mul(t_matrix *a, t_matrix *b);
t_matrix	*mat_identity(size_t row, size_t col);
t_matrix	*mat_transpose(t_matrix *mat);
t_matrix	*mat_dup(t_matrix *src);
t_matrix	*mat_submat(t_matrix *src, size_t rm_row, size_t rm_col);
double		mat_det(t_matrix *mat);
t_matrix	*mat_inv(t_matrix *src);
double		mat_inner(t_matrix *a, t_matrix *b);
double		mat_get_x(t_vector *vector);
double		mat_get_y(t_vector *vector);
double		mat_get_z(t_vector *vector);

/* affine */
t_affine	*mat_affine_new(size_t dimension);
void		mat_affine_free(t_affine **affine);
t_matrix	*mat_rotation_2d_new(double theta, t_affine *src);
void		mat_rotation_2d(double theta, t_affine *dst);
t_matrix	*mat_rotation_x(double alpha);
t_matrix	*mat_rotation_y(double beta);
t_matrix	*mat_rotation_z(double gamma);
t_matrix	*mat_rotation_any(t_matrix *vec, double theta);
t_matrix	*mat_translation_3d(double x, double y, double z);
void		mat_translation_2d(double x, double y, t_affine *src);
t_matrix	*mat_translation_2d_new(double x, double y, t_affine *src);
t_matrix	*mat_zoom_3d(double x, double y, double z);
t_matrix	*mat_zoom_2d_new(double x, double y, t_affine *src);
void		mat_zoom_2d(double x, double y, t_affine *dst);
t_matrix	*mat_vector_col_2d(double x, double y);
t_matrix	*mat_vector_row_2d(double x, double y);
t_matrix	*mat_vector_col_3d(double x, double y, double z);
t_matrix	*mat_vector_row_3d(double x, double y, double z);
double		mat_l2norm(t_matrix *matrix);
double		mat_distance_2d(t_matrix *matrix);

/* debug */
void		mat_print(t_matrix *mat);

#endif
