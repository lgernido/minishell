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

#include "data_structures_define_and_includes.h"
#include "minishell.h"

int	ft_and_alone(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '&' && i == 0 && (str[i + 1] == ' ' || str[i
						+ 1] == '\0')) || (str[i] == '&' && i > 0 && (str[i
						+ 1] == ' ' || str[i + 1] == '\0')
				&& str[i - 1] != '&'))
		{
			str[i] *= -1;
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
	else if (ft_and_alone(str))
		return (1);
	else
		return (0);
}

void	remove_newline(t_token *token_stream)
{
	while (token_stream->next->type != T_NEWLINE)
	{
		token_stream = token_stream->next;
	}
	free(token_stream->next->value);
	free(token_stream->next);
	token_stream->next = NULL;
}

int	ft_start_parse(t_core *minishell, char *str)
{
	char	*token;

	if (ft_syntax_check(str) != 0)
	{
		free(str);
		minishell->error_code = 2;
		return (1);
	}
	else
	{
		ft_split_tokens(minishell, str);
		token = ft_tokenizer(minishell);
		if (token)
		{
			ft_dprintf(2, "minishell: syntax error near unexpected token '%s'\n",
				token);
			free(str);
			minishell->error_code = 2;
			return (1);
		}
		ft_here_doc(minishell);
	}
	free(str);
	remove_newline(minishell->token_list);
	return (0);
}
