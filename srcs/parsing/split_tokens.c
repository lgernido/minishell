/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:50:49 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/13 14:08:10 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokenize_variable(t_core *minishell, char *str, t_token **start, int i)
{
	int	token_start;

	token_start = i;
	i++;
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
		i++;
	ft_add_token_list(start, ft_create_token(minishell, token_start, str));
	return (i);
}

int	ft_tokenize_regular(t_core *minishell, char *str, t_token **start, int i)
{
	int	token_start;

	token_start = i;
	while (str[i] && !ft_find_char_str(str[i], " \t|;<>&()$"))
		i++;
	ft_add_token_list(start, ft_create_token(minishell, token_start, str));
	return (i);
}
int	ft_tokenize_special(t_core *minishell, char *str, t_token **start, int i)
{
	if (str[i] == '&' && str[i + 1] == '&')
	{
		ft_add_token_list(start, ft_create_token(minishell, i, "&&"));
		return (i + 2);
	}
	else if (str[i] == '|' && str[i + 1] == '|')
	{
		ft_add_token_list(start, ft_create_token(minishell, i, "||"));
		return (i + 2);
	}
	else
	{
		ft_add_token_list(start, ft_create_token(minishell, i, str));
		return (i + 1);
	}
}

void	ft_split_tokens(t_core *minishell, char *str)
{
	int		i;
	t_token	**start;

	i = 0;
	start = &minishell->token_list;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			i++;
			continue ;
		}
		if (str[i] == '$' && ft_isalpha(str[i + 1]))
			i = ft_tokenize_variable(minishell, str, start, i);
		else if (ft_find_char_str(str[i], "|;<>&()$"))
			i = ft_tokenize_special(minishell, str, start, i);
		else
			i = ft_tokenize_regular(minishell, str, start, i);
	}
	ft_add_token_list(start, ft_create_arg_token(minishell, "newline",
			T_NEWLINE));
}
