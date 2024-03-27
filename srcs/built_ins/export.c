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

<<<<<<< HEAD
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
=======
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
>>>>>>> lucie
}

static int	parse_var(char *str)
{
<<<<<<< HEAD
	int		ret_value;

	ret_value = check_forbidden_var(str);
	if (ret_value == 0)
	{
		ret_value = parse_before_equal_sign(str);
	}
	return (ret_value);
}

int	loop_trough_var(char **av, t_core *core)
=======
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
>>>>>>> lucie
{
	char	**addr;
	int		ret_value;

<<<<<<< HEAD
	ret_value = 0;
=======
	av++;
	if (!*av)
	{
		print_export(core);
		return (0);
	}
>>>>>>> lucie
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
