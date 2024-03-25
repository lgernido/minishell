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

void	print_stream_after_parse(t_token *stream)
{
	char	*tab[] = {"T_WORD", "T_REDIRECT", "T_PIPE",
								"T_PIPE", "T_NEWLINE", "T_AND", "T_OR",
								"T_PAR_OPEN", "T_PAR_CLOSE", "T_INPUT",
								"T_OUTPUT", "T_EXPAND", "T_HEREDOC",
								"T_TO_EXPAND", "T_NO_EXPAND", "T_SIMPLE_QUOTES",
								"T_DOUBLE_QUOTES", "T_LIM"};
	while (stream != NULL)
	{
		printf("Type : %s\n", tab[stream->type]);
		printf("Value :%s\n\n", stream->value);
		stream = stream->next;
	}
	return ;
}

void	minishell_driver(t_core *core)
{
	char	*user_input;

	init_sig();
	user_input = fetch_input(core->error_code);
	if (g_signal == 130)
	{
		react_sig(core);
	}
	if (user_input == NULL)
	{
		printf("exit\n");
		ft_clean_exit(core, core->error_code);
	}
	if (ft_start_parse(core, user_input) == 0)
	{
		print_stream_after_parse(core->token_list);
		ast_init((t_token_stream_node *)core->token_list, core);
		if (core->ast != NULL)
		{
			ast_driver(core);
		}
	}
	clean_prev_command(core);
}
