/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_error2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:02:42 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/22 16:02:43 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_error(void *arg)
{
	const int	errsv = errno;

	(void)arg;
	ft_printf_err("minishell: echo :%s\n", strerror(errsv));
	return ;
}
