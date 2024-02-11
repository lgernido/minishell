/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shell_lvl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:57:08 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/08 19:57:08 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "built_ins.h"
#include "printerr.h"

static t_bool	is_valid_nbr(char *shell_lvl_content)
{
	size_t	i;
	t_bool	return_value;

	i = 0;
	return_value = TRUE;
	while (shell_lvl_content[i] && i < 10)
	{
		if (!ft_isdigit(shell_lvl_content[i]))
			return_value = FALSE;
		i++;
	}
	if (i == 10)
	{
		return_value = FALSE;
	}
	return (return_value);
}

static	size_t	parse_content(char	*shell_lvl_content)
{
	size_t	shell_level;

	shell_level = 0;
	if (is_valid_nbr(shell_lvl_content) == TRUE)
	{
		shell_level = ft_atoi(shell_lvl_content);
	}
	if (shell_level + 2 >= 1000)
	{
		ft_printf_err("minishell: warning: shell level (%d)\
too high, resetting to 1\n", shell_level);
		shell_level = 0;
	}
	return (shell_level + 1);
}

void	export_shell_lvl(t_core *core, int shell_level)
{
	char	*shell_level_to_array;

	shell_level_to_array = ft_itoa(shell_level);
	if (!shell_level_to_array)
	{
		ft_clean_exit(core, MALLOC);
	}
	swap_var(core, shell_level_to_array, "SHLVL");
}

void	update_shell_lvl(t_core *core)
{
	char	*shell_lvl_content;
	size_t	shell_level;

	shell_level = 0;
	shell_lvl_content = ft_getenv(core, "$SHLVL");
	if (shell_lvl_content)
	{
		shell_level = parse_content(shell_lvl_content);
		free(shell_lvl_content);
	}
	export_shell_lvl(core, shell_level);
	return ;
}
