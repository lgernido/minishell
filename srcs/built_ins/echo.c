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
#include "built_ins.h"

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

static void	print_args(char **av)
{
	while (*av)
	{
		ft_printf("%s", *av);
		av++;
		if (*av)
			ft_printf(" ");
	}
}

int	ft_echo(char **av, t_core *core)
{
	t_bool	flag;

	((void)core);
	flag = FALSE;
	av++;
	if (*av)
		flag = is_flag(*av);
	print_args(av + flag);
	if (!flag)
		ft_printf("\n");
	return (0);
}
