/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_error_message.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:37:14 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/20 19:37:15 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"
#include "printerr.h"
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

void	not_regular(void *arg)
{
	ft_printf_err("minishell: %s: not a regular file.\n", arg);
	return ;
}

void	is_dir(void *arg)
{
	ft_printf_err("minishell: %s: Is a directory.\n", arg);
	return ;
}

void	lstat_error(void *arg)
{
	const char	*error = strerror(errno);

	ft_printf_err("minishell: %s: %s\n", arg, error);
}
