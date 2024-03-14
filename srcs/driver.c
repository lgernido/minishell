/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:22:06 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/14 12:32:24 by lgernido         ###   ########.fr       */
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

int	check_i_o(t_token_stream_node **inputs, t_token_stream_node **outputs)
{
	int	return_value;

	return_value = 0;
	return_value += check_redirections(inputs, verify_inputs, STD_IN_DEV,
			STD_IN_PROC);
	return_value += check_redirections(outputs, verify_outputs, STD_OUT_DEV,
			STD_OUT_PROC);
	return (return_value);
}

int	split_stream_driver(t_token_stream_node **split_stream,
		t_command_node *command_node)
{
	t_token_stream_node	*inputs;
	t_token_stream_node	*outputs;
	int					return_value;

	return_value = 0;
	shrink_stream(split_stream);
	inputs = build_operator_stream(split_stream, find_input_operator);
	outputs = build_operator_stream(split_stream, find_output_operator);
	if (errno == ENOMEM)
	{
		return (MALLOC);
	}
	return_value = check_i_o(&inputs, &outputs);
	if (return_value == 0)
	{
		return_value = build_command_node(split_stream, &inputs, &outputs,
				command_node);
	}
	else
	{
		ft_token_stream_clear(&inputs);
		ft_token_stream_clear(&outputs);
	}
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
	char	*user_input;

	// t_token_stream_node	*tokenized_user_input;
	if (g_signal == 1)
	{
		react_sig(core);
	}
	user_input = fetch_input(core, core->error_code);
	// tokenized_user_input = split_str(core, user_input);
	// ast_init(tokenized_user_input, core);
	// ast_driver(core);
}
