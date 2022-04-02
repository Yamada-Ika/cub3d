/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:31:44 by iyamada           #+#    #+#             */
/*   Updated: 2021/10/26 12:42:53 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*prev_lst;
	t_list	*next_lst;

	if (lst == NULL || *lst == NULL)
		return ;
	next_lst = *lst;
	while (next_lst != NULL)
	{
		prev_lst = next_lst;
		next_lst = next_lst->next;
		ft_lstdelone(prev_lst, (*del));
	}
	*lst = NULL;
}
