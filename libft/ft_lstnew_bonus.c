/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:14:45 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/13 10:47:47 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof (t_list));
	if (new_node != NULL)
	{
		new_node->content = content;
		new_node->next = NULL;
	}
	return (new_node);
}

/*int	main(void)
{
	t_list	*node1;
	t_list	*node2;
	char	*str = "cest bon";
	int		n = 42;

	node1 = ft_lstnew(str);
	node2 = ft_lstnew(&n);
	ft_putendl_fd(node1->content, 1);
	ft_putnbr_fd(*(int *)(node2->content), 1);
	ft_putchar_fd('\n', 1);
	free (node1);
	free(node2);
	return (0);
}*/
