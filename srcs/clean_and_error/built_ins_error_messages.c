/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_error_messages.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:27:28 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/22 12:27:28 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	throw_error_message(void *arg, void (*message)(void *))
{
	message(arg);
	return (1);
}

void	too_many_args(void *arg)
{
	(void)arg;
	ft_printf_err("minishell: cd: too many arguments\n");
	return ;
}

void	home_not_set(void *arg)
{
	(void)arg;
	ft_printf_err("minishell: cd: HOME not set\n");
	return ;
}

void	error_while_shifting_directory(void *arg)
{
	ft_printf_err("minishell: cd: %s:%s", strerror(errno), arg);
	return ;
}

void	export_error(void *arg)
{
	ft_printf_err("minishell: export: `%s':\
not a valid identifier\n", (char *)arg);
}
