/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:13:28 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/22 12:13:28 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name_end(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] != '\0' && var[i] != '=')
	{
		++i;
	}
	return (&var[i]);
}

static void	print_var(char *var)
{
	char	*var_name_end;
	char	var_end;

	var_name_end = get_var_name_end(var);
	var_end = *var_name_end;
	*var_name_end = '\0';
	ft_printf("%s", var);
	if (var_end == '=')
	{
		ft_printf("=\"%s\"", var_name_end + 1);
	}
	*var_name_end = var_end;
	ft_printf("\n");
}

void	print_export(t_core *core)
{
	int	i;

	i = 0;
	while (i < core->env_size)
	{
		if (core->env[i] != NULL)
		{
			ft_printf("declare -x ");
			print_var(core->env[i]);
		}
		++i;
	}
	return ;
}
