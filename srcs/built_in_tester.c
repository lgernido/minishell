/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitl_in_tester.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:01:02 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/09 15:01:02 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_built_in(char	*asked_command, char **available_commands)
{
	const size_t	len = ft_strlen(asked_command);
	size_t			i;

	i = 0;
	while (available_commands[i])
	{
		if (!ft_strncmp(asked_command, available_commands[i], len))
			break ;
		i++;
	}
	if (available_commands[i] == NULL)
	{
		i = -1;
	}
	return (i);
}

void	call_functions(t_test *test)
{
	int	i;

	i = get_built_in(test->splitted_cli[0], test->splitted_cmds);
	if (i == -1)
	{
		ft_printf_err("minishell :%s: built-in not found\n",
			test->splitted_cli[0]);
		test->core->error_code = 127;
	}
	else
	{
		test->core->error_code = test->built_in_arr[i]
			(test->splitted_cli, test->core);
	}
	return ;
}

void	run_built_ins(t_core *core, char *command_line)
{
	t_test	test;

	test.core = core;
	if (ft_strlen(command_line) == 0)
	{
		return ;
	}
	init_built_in_array(&test);
	split_cmd_and_cli(&test, command_line);
	call_functions(&test);
	exit_test(&test);
	return ;
}
