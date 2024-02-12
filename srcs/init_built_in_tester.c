/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_built_in_tester.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:59:27 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/09 15:59:27 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_test(t_test *test)
{
	if (test->splitted_cli != NULL)
	{
		ft_free_tab(test->splitted_cli);
	}
	if (test->splitted_cmds != NULL)
	{
		ft_free_tab(test->splitted_cmds);
	}
}

void	init_built_in_array(t_test *test)
{
	test->built_in_arr[0] = ft_pwd;
	test->built_in_arr[1] = ft_echo;
	test->built_in_arr[2] = ft_cd;
	test->built_in_arr[3] = ft_exit;
	test->built_in_arr[4] = ft_export;
	test->built_in_arr[5] = ft_env;
	test->built_in_arr[6] = ft_unset;
}

void	split_cmd_and_cli(t_test *test, char *command_line)
{
	test->splitted_cmds = ft_split("pwd echo cd exit export env unset", ' ');
	if (test->splitted_cmds == NULL)
	{
		exit_test(test);
		ft_clean_exit(test->core, EXIT_FAILURE);
	}
	test->splitted_cli = ft_split(command_line, ' ');
	if (test->splitted_cli == NULL)
	{
		exit_test(test);
		ft_clean_exit(test->core, EXIT_FAILURE);
	}
}
