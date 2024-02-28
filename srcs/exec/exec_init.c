/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:59:27 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/28 17:59:27 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_built_in(char *command)
{
	const char		**built_ins = (const char **)ft_split
		("env export unset cd pwd exit echo", ' ');
	const size_t	command_len = ft_strlen(command) + 1;
	int				i;

	i = 0;
	if (built_ins == NULL)
	{	
		return (FALSE);
	}
	while (built_ins[i] != NULL)
	{
		if (ft_strncmp(command, built_ins[i], command_len) == 0)
		{
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	exec_init(t_core *core)
{
	while (core->ast->command_list != NULL)
	{
		if (is_built_in(core->ast->command_list->cmd[0]) == TRUE)
		{
			//
		}
		else
		{
			check_errno(core);
			// do other thing
		}
		core->ast->command_list = core->ast->command_list->next;
	}
}
