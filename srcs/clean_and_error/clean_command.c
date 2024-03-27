/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:07:09 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 19:07:10 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "minishell.h"
#include "clean_and_error.h"

void	close_if_open(int *fd)
{
	if (*fd != -1)
	{
		close (*fd);
		*fd = -1;
	}
	return ;
}

void	ft_clean_node(t_command_node *node)
{
	close_if_open(&node->fd_infile);
	close_if_open(&node->fd_outfile);
	close_if_open(&node->pipe[READ_ENTRY]);
	close_if_open(&node->pipe[WRITE_ENTRY]);
	close_if_open(&node->saved_infile);
	close_if_open(&node->saved_outfile);
	ft_clear_token_stream_if_needed(&node->redirections);
	if (node->here_doc != NULL)
	{
		free(node->here_doc);
	}
	if (node->cmd != NULL)
	{
		ft_free_tab(node->cmd);
	}
}

void	climb_command_list_to_origin(t_command_node **list)
{
	while ((*list)->prev != NULL)
	{
		*list = (*list)->prev;
	}
}

void	ft_command_clear(t_command_node **list)
{
	t_command_node	*tmp;

	climb_command_list_to_origin(list);
	while (*list)
	{
		tmp = (*list)->next;
		ft_clean_node(*list);
		free(*list);
		*list = tmp;
	}
}

<<<<<<< HEAD:srcs/clean_exit.c
void	ft_free_env(t_core *core)
{
	int	i;

	i = 0;
	while (i < core->env_size)
	{
		free_if_needed(&(core->env[i]));
		i++;
	}
	free(core->env);
}

void	ft_clean_exit(t_core *core, int code)
{
	if (core->env)
		ft_free_env(core);
	if (core->command_list)
		ft_command_clear(&core->command_list);
	rl_clear_history();
	exit(code);
=======
void	exit_from_child(t_core *core, int code)
{
	close(0);
	close(1);
	close(2);
	ft_clean_exit(core, code);
>>>>>>> lucie:srcs/clean_and_error/clean_command.c
}
