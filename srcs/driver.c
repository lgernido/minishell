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

<<<<<<< HEAD
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

=======
>>>>>>> resolve_operator
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
<<<<<<< HEAD
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
=======
	return_value = build_command_node(split_stream, command_node);
>>>>>>> resolve_operator
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

void	minishell_driver(t_core *core)
{
	char	*user_input;

<<<<<<< HEAD
	// t_token_stream_node	*tokenized_user_input;
	if (g_signal == 1)
	{
		react_sig(core);
	}
	user_input = fetch_input(core, core->error_code);
	// tokenized_user_input = split_str(core, user_input);
	// ast_init(tokenized_user_input, core);
	// ast_driver(core);
=======
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
	tokenized_user_input = split_str(core, user_input);
	ast_init(tokenized_user_input, core);
	ast_driver(core);
	clean_prev_command(core);
>>>>>>> resolve_operator
}
