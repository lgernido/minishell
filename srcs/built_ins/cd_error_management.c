/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:12:44 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/08 14:12:47 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
<<<<<<< HEAD:srcs/built_ins/cd_error_management.c

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
	ft_printf_err("minishell: cd: %s:%s\n", strerror(errno), arg);
	return ;
=======
#include "clean_and_error.h"

int	go_specified_dir(void *path)
{
	const int	return_value = chdir(path);

	if (return_value == -1)
	{
		throw_error_message(path, error_while_shifting_directory);
	}
	else
	{
		return (0);
	}
	return (return_value);
>>>>>>> lucie:srcs/built_ins/cd_utils.c
}
