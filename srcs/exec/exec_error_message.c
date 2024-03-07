/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_message.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 07:48:38 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/05 07:48:39 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "built_ins.h"

void	command_not_found(void *arg)
{
	ft_printf_err("minishell: command not found: %s\n", (char *)arg);
}

void	permission_denied(void *arg)
{
	ft_printf_err("minishell: permission denied: %s\n", (char *)arg);
}

void	throw_exec_message(void *arg)
{
	if (errno == ENOENT)
	{
		throw_error_message(arg, command_not_found);
	}
	else
	{
		throw_error_message(arg, permission_denied);
	}
}

void	lstat_error(void *arg)
{
	const int	errsv = errno;

	(void)arg;
	ft_printf_err("minishell: lstat: %s\n", strerror(errsv));
}

void	open_file_error(void *arg)
{
	const int	errsv = errno;

	ft_printf_err("minishell: %s: %s\n", (char *)arg, strerror(errsv));
}
