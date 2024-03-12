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

#include "exec.h"

void	exec_error(void *arg)
{
	const int	errsv = errno;

	ft_printf_err("minishell: %s: %s\n", (char *)arg, strerror(errsv));
	errno = errsv;
}

void	execve_failure(void *arg)
{
	const int	errsv = errno;

	if (errsv == ENOENT)
	{
		ft_printf_err("minishell: %s: command not found\n", (char *)arg);
	}
	else
	{
		ft_printf_err("minishell: %s: %s\n", (char *)arg, strerror(errsv));
	}
}
