/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls_with_internal_error_throwing.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:15:46 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/07 15:15:47 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "clean_and_error.h"

pid_t	checked_fork(void)
{
	const pid_t	pid = fork();

	if (pid == -1)
	{
		throw_error_message("fork", exec_error);
	}
	return (pid);
}

int	checked_pipe(int *pipedest)
{
	const int	return_value = pipe(pipedest);

	if (return_value == -1)
	{
		throw_error_message("pipe", exec_error);
	}
	return (return_value);
}

int	checked_dup2(int fd, int fd2)
{
	const int	return_value = dup2(fd, fd2);

	if (return_value == -1)
	{
		throw_error_message("dup2", exec_error);
	}
	return (return_value);
}

int	checked_dup(int fd)
{
	const int	fd_copy = dup(fd);

	if (fd_copy == -1)
	{
		throw_error_message("dup", exec_error);
	}
	return (fd_copy);
}
