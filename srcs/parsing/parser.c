/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:58:49 by luciegernid       #+#    #+#             */
/*   Updated: 2024/03/13 15:20:23 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_dprintf(2, "backslash can't be interpreted\n");
		return (1);
	}
	else
		return (0);
}

void	ft_start_parse(t_core *minishell, char *str)
{
	char	*token;

	if (ft_syntax_check(str) != 0)
		return ;
	else
	{
		ft_split_tokens(minishell, str);
		token = ft_tokenizer(minishell);
		if (token)
		{
			ft_dprintf(2,
				"minishell: syntax error near unexpected token `%s'\n", token);
			ft_clear_token_list(&minishell->token_list, free);
			return ;
		}
	}
	ft_discard_quotes(minishell);
}
