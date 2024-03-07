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

	(void)arg;
	ft_printf_err("minishell: %s: %s\n", strerror(errsv));
	errno = errsv;
}
