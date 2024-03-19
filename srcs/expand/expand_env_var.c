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
#include <readline/readline.h>

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

char	*get_var(t_core *core, char *var_begin, char *var_end)
{
	char	*var;
	char	*substitute_var;

	var = ft_strndup(var_begin, var_end);
	if (var == NULL)
	{
		return (NULL);
	}
	substitute_var = ft_getenv(core, var);
	return (substitute_var);
}

char	*substitute_var(t_core *core, char *str, char *var_begin, char *var_end)
{
	const char	*substitute_var = get_var(core, var_begin, var_end);
	char		*temp_str;

	temp_str = NULL;
	if (errno != ENOMEM)
	{
		*var_begin = '\0';
		if (substitute_var != NULL)
		{
			temp_str = ft_strjoin(str, substitute_var);
			free((char *)substitute_var);
			free(str);
			str = temp_str;
		}
		if (str != NULL)
		{
			temp_str = ft_strjoin(str, var_end);
			free(str);
		}
		return (expand_var_init(core, temp_str));
	}
	free(str);
	return (NULL);
}

char	*expand_var_init(t_core *core, char *str)
{
	size_t	i;
	char	*var_end;

	if (str == NULL)
	{
		return (str);
	}
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
