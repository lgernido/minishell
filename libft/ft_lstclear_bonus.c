/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:21:31 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/10 19:15:01 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	p = *lst;
	while (p)
	{
		del(p->content);
		tmp = p->next;
		free(p);
		p = tmp;
	}
	*lst = NULL;
	return ;
}
