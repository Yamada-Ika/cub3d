#include "vector.h"

t_vector	*vec_new(size_t type_size)
{
	t_vector	*new;

	new = ft_calloc(1, sizeof(t_vector));
	new->data = ft_calloc(128, type_size);
	new->cap = 128;
	new->type_size = type_size;
	return (new);
}


void	vec_push_back(t_vector *v, void *data)
{
	if (v->cap == v->len)
	{
		v->data = ft_realloc(v->data, (v->cap + 128) * v->type_size);
		v->cap += 128;
	}
	ft_memcpy(v->data + v->len * v->type_size, data, v->type_size);
	v->len++;
}

void	*vec_at(t_vector *v, size_t index)
{
	return (v->data + index * v->type_size);
}

void	vec_delete(t_vector *v, void *del(void *))
{
	(*del)(v->data);
	free(v);
}
