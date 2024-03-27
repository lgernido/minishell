/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:35:44 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/05 16:35:45 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_ins.h"
#include "clean_and_error.h"

static int	is_invalid(char c, int flag)
{
	if (!ft_isalnum(c) && c != '_' && flag == 0)
		return (1);
	else if (!ft_isalpha(c) && c != '_' && flag != 0)
		return (1);
	return (0);
}

static int	check_curr_char(char *current_char, char *str_beginning)
{
	if (current_char == str_beginning)
	{
		if (is_invalid(*current_char, 1))
		{
			throw_error_message(str_beginning, export_error);
			return (1);
		}
	}
	else
	{
		if (is_invalid(*current_char, 0))
		{
			throw_error_message(str_beginning, export_error);
			return (1);
		}
	}
	return (0);
}

static int	parse_var(char *str)
{
	char	*tmp;
	int		i;

	tmp = str;
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (check_curr_char(&str[i], tmp) == 1)
		{
			return (1);
		}
		++i;
	}
	if (i == 0)
	{
		throw_error_message(str, export_error);
		return (1);
	}
	return (0);
}

int	ft_export(char **av, t_core *core)
{
	char	**addr;

	av++;
	if (!*av)
	{
		print_export(core);
		return (0);
	}
	while (*av)
	{
		if (!parse_var(*av))
		{
			addr = get_valid_addr(core, *av);
			if (*addr)
				free(*addr);
			*addr = ft_strdup(*av);
		}
		av++;
	}
	return (0);
}
