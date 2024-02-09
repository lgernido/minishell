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

#include "libft.h"
#include "minishell.h"
#include "built_ins.h"

static void	print_export(char **env)
{
	while (*env)
	{
		if (is_set(*env))
			printf("declare -x \"%s\"\n", *env);
		env++;
	}
}

static int	check_forbidden_var(char *str)
{
	int			ret_value;

	ret_value = check_len(str);
	if (ret_value == 0)
	{
		ret_value = is_the_var_write_protected(str);
	}
	return (ret_value);
}

static int	parse_var(char *str)
{
	int		ret_value;

	ret_value = check_forbidden_var(str);
	if (ret_value == 0)
	{
		ret_value = parse_before_equal_sign(str);
	}
	return (ret_value);
}

int	loop_trough_var(char **av, t_core *core)
{
	char	**addr;
	int		ret_value;

	ret_value = 0;
	while (*av)
	{
		if (!parse_var(*av))
		{
			addr = get_valid_addr(core, *av);
			if (*addr)
				free(*addr);
			*addr = ft_strdup(*av);
		}
		else
		{
			ret_value = 1;
		}
		av++;
	}
	return (ret_value);
}

int	ft_export(char **av, t_core *core)
{
	int		ret_value;

	av++;
	ret_value = 0;
	if (!*av)
	{
		print_export(core->env);
		ret_value = 0;
	}
	else
	{
		ret_value = loop_trough_var(av, core);
	}
	return (ret_value);
}
