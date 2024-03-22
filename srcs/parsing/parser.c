/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:58:49 by luciegernid       #+#    #+#             */
/*   Updated: 2024/03/22 16:08:42 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_and_alone(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '&' && i == 0 && (str[i + 1] == ' ' || str[i
					+ 1] == '\0')) || (str[i] == '&' && i > 0 && (str[i
					+ 1] == ' ' || str[i + 1] == '\0') && str[i - 1] != '&'))
		{
			ft_dprintf(2, "syntax error :");
			ft_dprintf(2, "&& must be an operator or between quotes\n");
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
	else if (ft_and_alone(str))
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
		{
			minishell->error_code = 2;
			return (1);
		}
		else
		{
			ft_split_tokens(minishell, str);
			token = ft_tokenizer(minishell);
			if (token)
			{
				ft_dprintf(2,
					"minishell: syntax error near unexpected token '%s'\n",
					token);
				minishell->error_code = 2;
				return (1);
			}
			ft_here_doc(minishell);
		}
	}
	return (0);
}
