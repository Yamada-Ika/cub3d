/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:46:06 by iyamada           #+#    #+#             */
/*   Updated: 2021/10/21 16:57:53 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_ptr;

	if (lst == NULL || (*f) == NULL)
		return (NULL);
	new = ft_lstnew((*f)(lst->content));
	new_ptr = new;
	lst = lst->next;
	while (lst != NULL)
	{
		new->next = ft_lstnew((*f)(lst->content));
		if (new->next == NULL)
		{
			ft_lstclear(&new, (*del));
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (new_ptr);
}
