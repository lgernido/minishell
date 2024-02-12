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
	if (*str == '-')
		str++;
	else
		return (FALSE);
	while (*str == 'n')
		str++;
	if (*str)
		return (FALSE);
	return (TRUE);
}

static void	print_args(char **av)
{
	while (*av)
	{
		printf("%s", *av);
		av++;
		if (*av)
			printf(" ");
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
		printf("\n");
	return (0);
}
