/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:52:18 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/18 16:52:18 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "expand.h"

static t_bool	is_valid_var_ender(char c)
{
	if (c == ' ' || c == '\t' || c == '\0' || c == '$')
	{
		return (TRUE);
	}
	return (FALSE);
}

char	*find_var_end(char *var_begin)
{
	while (is_valid_var_ender(*(var_begin + 1)) == FALSE)
	{
		++var_begin;
	}
	return (var_begin);
}

char	*substitute_var(t_core *core, char *str, char *var_begin, char *var_end)
{
	const char	*extracted_var = ft_strndup(var_begin, var_end);
	const char	*replaced_var = ft_getenv(core, (char *)extracted_var);
	char		*new_str;
	char		*temp_str;

	if (errno == ENOMEM)
	{
		return (NULL);
	}
	*var_begin = '\0';
	if (replaced_var != NULL)
	{
		temp_str = ft_strjoin(var_begin, replaced_var);
		if (temp_str != NULL)
		{
			new_str = temp_str;
		}
	}
	temp_str = ft_strjoin(new_str, var_end);
	free(str);
	if (temp_str == NULL)
	{
		return (NULL);
	}
	return (expand_var_init(core, temp_str));
}

char	*expand_var_init(t_core *core, char *str)
{
	size_t	i;
	char	*var_end;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '$'
			&& is_valid_var_ender(str[i + 1]) == FALSE)
		{
			var_end = find_var_end(&str[i]);
			return (substitute_var(core, str, str + i, var_end));
		}
		++i;
	}
	return (str);
}
