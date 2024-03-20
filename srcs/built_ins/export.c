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

static int	is_invalid(char c, int flag)
{
	if (!ft_isalnum(c) && c != '_' && flag == 0)
		return (1);
	else if (!ft_isalpha(c) && c != '_' && flag != 0)
		return (1);
	return (0);
}

void	export_error(void *arg)
{
	ft_printf_err("minishell: export: `%s':\
not a valid identifier\n", (char *)arg);
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

	tmp = str;
	while (*str != '=')
	{
		if (check_curr_char(str, tmp) == 1)
		{
			return (1);
		}
		str++;
		if (!*str)
			return (1);
	}
	if (!*(str + 1))
		return (1);
	return (0);
}

char	**ft_realloc_env(char **env, int *size)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = ft_calloc(*size * 2, sizeof(char *));
	if (!new_envp)
	{
		ft_free_tab(env);
		return (NULL);
	}
	while (env[i])
	{
		new_envp[i] = env[i];
		i++;
	}
	free(env);
	*size *= 2;
	return (new_envp);
}

char	**get_valid_addr(t_core *core, char *av)
{
	int		i;
	char	**to_comp;

	i = 0;
	to_comp = ft_split(av, '=');
	if (!to_comp)
		ft_clean_exit(core, MALLOC);
	while (core->env[i] != NULL && i < core->env_size - 1)
	{
		if (is_the_var(*to_comp, core->env[i]))
			break ;
		++i;
	}
	ft_free_tab(to_comp);
	if (i < core->env_size - 1)
		return (&core->env[i]);
	else
	{
		core->env = ft_realloc_env(core->env, &core->env_size);
		if (!core->env)
			ft_clean_exit(core, MALLOC);
		return (get_valid_addr(core, av));
	}
}

int	ft_export(char **av, t_core *core)
{
	char	**addr;

	av++;
	if (!*av)
	{
		print_export(core->env);
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
