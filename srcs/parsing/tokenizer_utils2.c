/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:03:55 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/19 13:14:43 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokenize_redirections(t_core *minishell, char *str, t_token **start,
		int i)
{
	if (str[i] == '>' && str[i + 1] == '>')
	{
		ft_add_token_list(start, ft_create_priority_token(
				minishell, ">>", str));
		return (i + 2);
	}
	else if (str[i] == '<' && str[i + 1] == '<')
	{
		ft_add_token_list(start, ft_create_priority_token(
				minishell, "<<", str));
		return (i + 2);
	}
	else if (str[i] == '<')
	{
		ft_add_token_list(start, ft_create_priority_token(minishell, "<", str));
		return (i + 1);
	}
	else if (str[i] == '>')
	{
		ft_add_token_list(start, ft_create_priority_token(minishell, ">", str));
		return (i + 1);
	}
	else
		return (i);
}

int	ft_tokenize_parenthesis(t_core *minishell, char *str, t_token **start,
		int i)
{
	if (str[i] == '(')
	{
		ft_add_token_list(start, ft_create_priority_token(minishell, "(", str));
		return (i);
	}
	else
	{
		ft_add_token_list(start, ft_create_priority_token(minishell, ")", str));
		return (i);
	}
}

int	ft_handle_squote(t_core *minishell, char *user_input, int *i,
		t_token **start)
{
	int		j;
	char	*new_value;

	if (user_input[*i] == '\'')
	{
		j = *i + 1;
		while (user_input[j] && user_input[j] != '\'')
			j++;
		if (j == *i + 1)
			return (*i + 1);
		else
		{
			new_value = ft_substr(user_input, *i + 1, j - *i - 1);
			if (!new_value)
				ft_clean_exit(minishell, MALLOC);
			ft_add_token_list(start, ft_create_arg_token(minishell, new_value,
					T_SIMPLE_QUOTES, user_input));
			*i = j + 1;
			free(new_value);
			return (*i);
		}
	}
	return (*i);
}

int	ft_handle_dquote(t_core *minishell, char *user_input, int *i,
		t_token **start)
{
	int		j;
	char	*new_value;

	if (user_input[*i] == '\"')
	{
		j = *i + 1;
		while (user_input[j] && user_input[j] != '\"')
			j++;
		if (j == *i + 1)
			return (*i + 1);
		else
		{
			new_value = ft_substr(user_input, *i + 1, j - *i - 1);
			if (!new_value)
				ft_clean_exit(minishell, MALLOC);
			ft_add_token_list(start, ft_create_arg_token(minishell, new_value,
					T_DOUBLE_QUOTES, user_input));
			*i = j + 1;
			free(new_value);
			return (*i);
		}
	}
	return (*i);
}
