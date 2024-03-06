/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_to_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:22:36 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/01 17:22:37 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "libft.h"
#include "minishell.h"
#include "printerr.h"
#include <unistd.h>

void	append_backslash(char **path_tab)
{
	char	*tmp_str;
	size_t	i;

	i = 0;
	while (path_tab[i] != NULL)
	{
		tmp_str = ft_strjoin(path_tab[i], "/");
		if (tmp_str == NULL)
		{
			break ;
		}
		free(path_tab[i]);
		path_tab[i] = tmp_str;
		++i;
	}
	return ;
}

char	**split_path(char *path)
{
	char	**splitted_path;

	splitted_path = ft_split(path, ':');
	free(path);
	if (splitted_path != NULL)
	{
		append_backslash(splitted_path);
	}
	return (splitted_path);
}

void	assemble_command(char **possible_path, char *command_to_exec)
{
	char	*joined_str;
	size_t	i;

	i = 0;
	while (possible_path[i] != NULL)
	{
		joined_str = ft_strjoin(possible_path[i], command_to_exec);
		if (joined_str == NULL)
		{
			break ;
		}
		if (access(joined_str, F_OK) == 0)
		{
			free(command_to_exec);
			command_to_exec = joined_str;
			break ;
		}
		free(joined_str);
		++i;
	}
	return ;
}

void	retrieve_path(t_core *core, t_command_node *current_command)
{
	char	*path;
	char	**splitted_path;

	path = ft_getenv(core, "$PATH");
	check_errno(core);
	splitted_path = split_path(path);
	check_errno(core);
	assemble_command(splitted_path, current_command->cmd[0]);
	check_errno(core);
	return ;
}
