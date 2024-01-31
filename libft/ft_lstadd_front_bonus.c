/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:44:08 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/10 10:22:40 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **list, t_list *new)
{
	if (!list || !new)
		return ;
	new->next = *list;
	*list = new;
	return ;
}

/*int	main(void)
{
	t_list	*node;
	t_list	*new;
	int	n = 42;

	node = malloc(sizeof (t_list));
	new = malloc(sizeof (t_list));
	node->content = &n;
	ft_lstadd_front(&node, new);
	ft_putnbr_fd(*(int *)new->next->content, 1);
	free(node);
	free(new);
}*/
