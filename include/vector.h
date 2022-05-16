/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:08:51 by kkaneko           #+#    #+#             */
/*   Updated: 2022/05/16 01:19:09 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include "libft.h"

typedef struct s_vector {
	void	*data;
	size_t	cap;
	size_t	len;
	size_t	type_size;
}	t_vector;

t_vector	*vec_new(size_t type_size);
void		vec_push_back(t_vector *v, void *data);
void		*vec_at(t_vector *v, size_t index);
void		vec_delete(t_vector *v, void *del(void *));

#endif
