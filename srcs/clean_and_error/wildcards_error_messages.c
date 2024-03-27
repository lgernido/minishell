/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_error_messages.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:19:03 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 17:19:03 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ambiguous_redir(void *arg)
{
	ft_printf_err("minishell: %s: ambiguous redirect\n", (char *)arg);
	return ;
}

void	opendir_error(void *arg)
{
	const int	errsv = errno;

	ft_printf_err("minishell: opendir: %s: %s\n", (char *)arg, strerror(errsv));
	errno = errsv;
}
