/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:32:53 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/09 13:32:54 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_ins.h"

char	*build_var(const char *s1, const char *s2)
{
	char	*joined_str;
	char	*tmp;

	joined_str = NULL;
	tmp = ft_strjoin(s1, "=");
	if (tmp != NULL)
	{
		joined_str = ft_strjoin(tmp, s2);
		free(tmp);
	}
	return (joined_str);
}

void	free_if_needed(char **str)
{
	if (*str != NULL)
		free(*str);
}

void	swap_var(t_core *core, char *var_content, const char *var_name)
{
	char		**var_address;
	char		*full_var;

	var_address = get_valid_addr(core, (char *)var_name);
	free_if_needed(var_address);
	full_var = build_var(var_name, var_content);
	if (!full_var)
	{
		ft_clean_exit(core, MALLOC);
	}
	*var_address = ft_strdup(full_var);
	free(full_var);
	if (*var_address == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	free(var_content);
}
