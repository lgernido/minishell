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

static t_bool	is_flag(char *str)
{
	if (*str == '-')
		str++;
	else
		return (TRUE);
	while (*str)
	{
		if (*str != 'n')
			return (TRUE);
		str++;
	}
	return (FALSE);
}

int	echo(char **av)
{
	t_bool	ending_new_line;

	ending_new_line = TRUE;
	av++;
	if (*av)
		ending_new_line = is_flag(*av);
	if (!ending_new_line)
		av++;
	while (*av)
	{
		printf("%s", *av);
		av++;
		if (*av)
			printf(" ");
	}
	if (ending_new_line)
		printf("\n");
	return (0);
}
