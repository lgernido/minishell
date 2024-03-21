/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:50:49 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/21 13:17:35 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokenize_quotes(t_core *minishell, char *str, t_token **start, int i)
{
	int	token_start;

	token_start = i;
	if (str[i] == '\"')
		i = ft_handle_dquote(minishell, str, &i, start);
	else if (str[i] == '\'')
		i = ft_handle_squote(minishell, str, &i, start);
	return (i);
}

int	ft_tokenize_variable(t_core *minishell, char *str, t_token **start, int i)
{
	int	token_start;

	token_start = i;
	i++;
	if (str[i] == '?')
	{
		ft_add_token_list(start, ft_create_priority_token(minishell, "$?"));
		return (i + 1);
	}
	else
	{
		while (str[i] && (ft_isalpha(str[i])))
			i++;
		ft_add_token_list(start, ft_create_token(minishell, token_start, str));
	}
	return (i);
}

int	ft_tokenize_regular(t_core *minishell, char *str, t_token **start, int i)
{
	int	token_start;

	token_start = i;
	while (str[i] && !ft_find_char_str(str[i], "\" \t|;<>&()$"))
		i++;
	ft_add_token_list(start, ft_create_token(minishell, token_start, str));
	return (i);
}

int	ft_tokenize_special(t_core *minishell, char *str, t_token **start, int i)
{
	if (str[i] == '&' && str[i + 1] == '&')
	{
		ft_add_token_list(start, ft_create_priority_token(minishell, "&&"));
		return (i + 2);
	}
	else if (str[i] == '|' && str[i + 1] == '|')
	{
		ft_add_token_list(start, ft_create_priority_token(minishell, "||"));
		return (i + 2);
	}
	else if (ft_find_char_str(str[i], "<>"))
	{
		i = ft_tokenize_redirections(minishell, str, start, i);
		return (i);
	}
	else
	{
		i = ft_tokenize_parenthesis(minishell, str, start, i);
		return (i + 1);
	}
}

void	ft_split_tokens(t_core *minishell, char *str)
{
	int		i;
	t_token	**start;

	i = 0;
	start = &minishell->token_list;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			i++;
			continue ;
		}
		else if (str[i] == '\"' || str[i] == '\'')
			i = ft_tokenize_quotes(minishell, str, start, i);
		else if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '?'))
			i = ft_tokenize_variable(minishell, str, start, i);
		else if (ft_find_char_str(str[i], "|<>&()"))
			i = ft_tokenize_special(minishell, str, start, i);
		else
			i = ft_tokenize_regular(minishell, str, start, i);
	}
	ft_add_token_list(start, ft_create_arg_token(minishell, "newline",
			T_NEWLINE));
}
