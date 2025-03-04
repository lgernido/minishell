/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:22:06 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 08:30:55 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "data_structures_define_and_includes.h"
#include "exec.h"
#include "minishell.h"
#include "clean_and_error.h"

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
	if (expand_init(core, core->ast->token_stream) == -1)
	{
		core->error_code = 1;
		choose_next_path_to_take(core);
		return ;
	}
	split_token_stream_by_pipes(core->ast);
	check_errno(core);
	i = 0;
	while (i < core->ast->number_of_split_streams && return_value == 0)
	{
		update_command_list(core);
		return_value = split_stream_driver(&core->ast->split_streams[i],
				core->ast->command_list);
		i++;
	}
	if (return_value != 0)
		ft_clean_exit(core, return_value);
	ft_split_stream_clean(core->ast);
	exec_driver(core);
	return ;
}

void	interpret_command(t_core *core, char *user_input)
{
	parsing_sig();
	if (ft_start_parse(core, user_input) == 0 && g_signal != 130)
	{
		init_sig();
		ast_init(core->token_list, core);
		if (core->ast != NULL)
		{
			ast_driver(core);
		}
	}
	if (g_signal == 130)
	{
		react_sig(core);
	}
}

void	minishell_driver(t_core *core)
{
	char	*user_input;

	init_sig();
	user_input = fetch_input();
	if (g_signal == 130)
	{
		react_sig(core);
	}
	if (user_input == NULL)
	{
		printf("exit\n");
		free_if_needed(&user_input);
		ft_clean_exit(core, core->error_code);
	}
	if (ft_strlen(user_input) > 0)
	{
		interpret_command(core, user_input);
	}
	else
	{
		free(user_input);
	}
	clean_prev_command(core);
}
