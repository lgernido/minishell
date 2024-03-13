/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handling_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:11:14 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/07 11:11:16 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_ins.h"
#include "exec.h"

void	get_down_stream(t_token_stream_node **stream)
{
	while ((*stream)->next != NULL)
	{
		*stream = (*stream)->next;
	}
	return ;
}

int	write_redirection_in_command_node(char *path, int *target_fd,
		int (*open_function)(char *))
{
	int	return_value;
	int	fd;

	return_value = 0;
	fd = open_file(path, open_function);
	if (fd != -1)
	{
		*target_fd = fd;
	}
	else
	{
		return_value = -1;
	}
	return (return_value);
}
