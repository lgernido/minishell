/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:48:15 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/03 17:48:16 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "clean_and_error.h"

static t_bool	is_flag(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == '-')
	{
		++i;
	}
	if (i == 0)
	{
		return (FALSE);
	}
	while (str[i] == 'n')
	{
		++i;
	}
	if (str[i] != '\0')
	{
		return (FALSE);
	}
	return (TRUE);
}

static int	print_args(char **av)
{
	int	return_value;

	return_value = 0;
	while (*av && return_value != -1)
	{
		return_value = ft_printf("%s", *av);
		av++;
		if (*av)
			return_value = ft_printf(" ");
	}
	if (return_value == -1)
	{
		throw_error_message(NULL, echo_error);
	}
	return (return_value);
}

int	ft_echo(char **av, t_core *core)
{
	t_bool	flag;

	((void)core);
	flag = FALSE;
	av++;
	if (*av)
		flag = is_flag(*av);
	if (print_args(av + flag) == -1)
	{
		return (1);
	}
	if (!flag)
	{
		if (ft_printf("\n") == -1)
		{
			throw_error_message(NULL, echo_error);
			return (1);
		}
	}
	return (0);
}
