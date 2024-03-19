/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:58:49 by luciegernid       #+#    #+#             */
/*   Updated: 2024/03/19 11:15:32 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1] != '\0')
	{
		if ((str[i] == '>' && (str[i + 1] != ' ' && str[i + 1] != '>'))
			|| (str[i] == '<' && (str[i + 1] != ' ' && str[i + 1] != '<')))
		{
			ft_dprintf(2, "redirection syntax : > file\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_syntax_check(char *str)
{
	if (ft_is_ascii(str))
	{
		ft_dprintf(2, "minishell: invalid ascii characters found in string\n");
		return (1);
	}
	else if (ft_quotes(str))
	{
		ft_dprintf(2, "unclosed quotes can't be interpreted\n");
		return (1);
	}
	else if (ft_handle_dollar(str))
	{
		ft_dprintf(2, "variable syntax : $VARIABLE\n");
		return (1);
	}
	else if (ft_handle_backslash(str))
	{
		ft_dprintf(2, "backslash and semicolon can't be interpreted\n");
		return (1);
	}
	else if (ft_handle_redirection(str))
		return (1);
	else
		return (0);
}

int	ft_start_parse(t_core *minishell, char *str)
{
	char	*token;

	if (str != NULL)
	{
		if (ft_syntax_check(str) != 0)
			return (1);
		else
		{
			ft_split_tokens(minishell, str);
			token = ft_tokenizer(minishell);
			if (token)
			{
				ft_clear_token_list(&minishell->token_list, free);
				ft_dprintf(2,
					"minishell: syntax error near unexpected token\n");
				return (1);
			}
		}
		// ft_discard_quotes(minishell);
	}
	return (0);
}
