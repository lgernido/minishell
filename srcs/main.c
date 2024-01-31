/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:31:19 by purmerinos        #+#    #+#             */
/*   Updated: 2024/01/31 09:50:19 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_input(t_command_node **list)
{
	char *str;

	while (1)
	{
		str = readline("minishell>");
		if (!str)
			ft_clean_exit(list, 0);
		add_history(str);
		// Input parsing fonction here, w/ list and str as argument. STR need to be free in the parsing !!
	}
}

int	main(void)
{
	t_command_node	*list;
	t_command_node	*node;

	node = NULL;
	list = NULL;
	node = init_node(node);
	if (!node)
		exit(MALLOC);
	node_add_back(&list, node);
	wait_input(&list);
}
