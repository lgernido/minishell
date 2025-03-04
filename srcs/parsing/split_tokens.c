/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:50:49 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/22 12:20:41 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokenize_quotes(t_core *minishell, char *str,
		t_token_stream_node**start, int i)
{
	if (str[i] == '\"')
		i = ft_handle_dquote(minishell, str, &i, start);
	else if (str[i] == '\'')
		i = ft_handle_squote(minishell, str, &i, start);
	return (i);
}

int	ft_tokenize_regular(t_core *minishell, char *str,
		t_token_stream_node**start, int i)
{
	int		token_start;
	char	end_of_token_copy;

	token_start = i;
	while (str[i] && !ft_find_char_str(str[i], "\" \t|<>&()"))
		i++;
	end_of_token_copy = str[i];
	str[i] = '\0';
	ft_add_token_list(start, ft_create_token(minishell, token_start, str));
	str[i] = end_of_token_copy;
	return (i);
}

int	ft_tokenize_special(t_core *minishell, char *str,
		t_token_stream_node **start, int i)
{
	if (str[i] == '&' && str[i + 1] == '&')
	{
		ft_add_token_list(start, ft_create_priority_token(
				minishell, "&&", str));
		return (i + 2);
	}
	else if (str[i] == '|' && str[i + 1] == '|')
	{
		ft_add_token_list(start, ft_create_priority_token(
				minishell, "||", str));
		return (i + 2);
	}
	else if (ft_find_char_str(str[i], "<>"))
	{
		i = ft_tokenize_redirections(minishell, str, start, i);
		return (i);
	}
	else if (ft_find_char_str(str[i], "()"))
	{
		i = ft_tokenize_parenthesis(minishell, str, start, i);
		return (i + 1);
	}
	ft_add_token_list(start, ft_create_priority_token(minishell, "|", str));
	return (i + 1);
}

void	ft_split_tokens(t_core *minishell, char *str)
{
	int					i;
	t_token_stream_node	**start;

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
			i = ft_handle_quoted_token(minishell, str, start, i);
		else if (ft_find_char_str(str[i], "|<>&()"))
			i = ft_tokenize_special(minishell, str, start, i);
		else
			i = tokenize_nested_quotes(minishell, str, start, i);
	}
	ft_add_token_list(start, ft_create_arg_token(minishell,
			"newline", T_NEWLINE, str));
}
