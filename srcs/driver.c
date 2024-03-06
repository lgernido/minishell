/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:22:06 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/22 17:22:07 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "minishell.h"

void	check_errno(t_core *core)
{
	if (errno == ENOMEM)
	{
		ft_clean_exit(core, MALLOC);
	}
}

int	split_stream_driver(t_token_stream_node **split_stream,
		t_command_node *command_node)
{
	int					return_value;

	return_value = 0;
	shrink_stream(split_stream);
	command_node->redirections = build_operator_stream(split_stream,
			find_redirection_operator);
	if (errno == ENOMEM)
	{
		return (MALLOC);
	}
	return_value = build_command_node(split_stream, command_node);
	return (return_value);
}

void	ast_driver(t_core *core)
{
	int		return_value;
	size_t	i;

	return_value = 0;
	split_token_stream_by_pipes(core->ast);
	check_errno(core);
	i = 0;
	while (i < core->ast->number_of_split_streams && return_value == 0)
	{	
		update_command_list(core);
		return_value = split_stream_driver(&core->ast->split_streams[i],
				core->ast->command_list);
		if (return_value == MALLOC)
		{
			ft_clean_exit(core, MALLOC);
		}
		i++;
	}
	if (return_value != 0)
	{
		ft_clean_exit(core, return_value);
	}
	ft_split_stream_clean(core->ast);
}

void	minishell_driver(t_core *core)
{
	char				*user_input;
	t_token_stream_node	*tokenized_user_input;

	if (g_signal == 1)
	{
		react_sig(core);
	}
	user_input = fetch_input(core->error_code);
	tokenized_user_input = split_str(core, user_input);
	ast_init(tokenized_user_input, core);
	ast_driver(core);
}
