/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:40:59 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/05 09:41:00 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_ins.h"
#include "exec.h"

int	is_built_in(char *command)
{
	const char		**built_ins = (const char **)ft_split
		("env export unset cd pwd exit echo", ' ');
	const size_t	command_len = ft_strlen(command) + 1;
	int				i;

	i = 0;
	if (built_ins == NULL)
	{	
		return (-1);
	}
	while (built_ins[i] != NULL)
	{
		if (ft_strncmp(command, built_ins[i], command_len) == 0)
		{
			return (i);
		}
		++i;
	}
	return (-1);
}

void	init_built_ins_tab(t_built_ins *built_ins_tab)
{
	built_ins_tab[0] = ft_env;
	built_ins_tab[1] = ft_export;
	built_ins_tab[2] = ft_unset;
	built_ins_tab[3] = ft_cd;
	built_ins_tab[4] = ft_pwd;
	built_ins_tab[5] = ft_exit;
	built_ins_tab[6] = ft_echo;
	return ;
}

void	save_std_fd(t_core *core, t_command_node *current_command)
{
	current_command->saved_infile = checked_dup(STDIN_FILENO);
	if (current_command->saved_infile == -1)
	{
		ft_clean_exit(core, errno);
	}
	current_command->saved_outfile = checked_dup(STDIN_FILENO);
	if (current_command->saved_outfile == -1)
	{
		ft_clean_exit(core, errno);
	}
	return ;
}

void	reset_std_fd(t_core *core, t_command_node *current_command)
{
	if (checked_dup2(current_command->saved_infile, STDIN_FILENO) == -1)
	{
		ft_clean_exit(core, errno);
	}
	if (checked_dup2(current_command->saved_outfile, STDOUT_FILENO) == -1)
	{
		ft_clean_exit(core, errno);
	}
	close_if_open(&current_command->saved_infile);
	close_if_open(&current_command->saved_outfile);
}

void	exec_built_ins(t_core *core, t_command_node *current_command,
		int command_index)
{
	t_built_ins	built_in_tab[7];

	init_built_ins_tab(built_in_tab);
	save_std_fd(core, current_command);
	if (redirection_driver(current_command) == -1)
	{
		ft_clean_node(current_command);
		core->error_code = 1;
		return ;
	}
	if (manage_input(current_command) == -1)
	{
		ft_clean_exit(core, 1);
	}
	if (manage_output(current_command) == -1)
	{
		ft_clean_exit(core, 1);
	}
	core->error_code = built_in_tab[command_index](current_command->cmd, core);
	reset_std_fd(core, current_command);
	return ;
}
