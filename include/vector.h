/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:08:51 by kkaneko           #+#    #+#             */
/*   Updated: 2022/06/08 15:07:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "libft.h"

typedef struct s_vector
{
	void		*data;
	long long	cap;
	long long	len;
	size_t		type_size;
}	t_vector;

t_vector	*vec_new(size_t type_size);
void		vec_push_back(t_vector *v, void *data);
void		*vec_at(t_vector *v, size_t index);
void		vec_delete(t_vector *v, void (*del)(void *));

#endif
