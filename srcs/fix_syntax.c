/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 08:01:58 by lgernido          #+#    #+#             */
/*   Updated: 2024/02/07 15:54:26 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_found(char *msg1, char *arg, char *msg2)
{
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(msg2, 2);
}

t_bool	ft_is_operator(t_token_type type)
{
	if (type >= 0 && type < 8)
		return (true);
	return (false);
}

void	ft_fix_redirection(t_token *token)
{
	int	size;

	size = ft_strlen(token->value);
	if (size > 2)
		ft_error_found("Syntax error :", token->value, "\n");
	else if (size == 2)
	{
		if (token->type == SIMPLE_REDIR_RIGHT)
			token->type = DOUBLE_REDIR_RIGHT;
		else
			token->type = DOUBLE_REDIR_LEFT;
	}
}

void	ft_fix_other_operators(t_token *token)
{
	int	size;

	size = ft_strlen(token->value);
	if (size > 2)
		ft_error_found("Syntax error :", token->value, "\n");
	else if (size == 2)
	{
		if (token->type == PIPELINE)
			token->type = OR;
		else if (token->type == SEMICOLON)
			ft_error_found("Syntax error :", token->value, "\n");
	}
	else if (size == 1)
	{
		if (token->type == AND)
			token->type = LITERAL;
	}
}

void	ft_fix_syntax(t_token token)
{
	if (ft_is_operator(token->type) == true)
	{
		if (token->type == SIMPLE_REDIR_LEFT)
			ft_fix_redirection(token);
		else if (token->type == SIMPLE_REDIR_RIGHT)
			ft_fix_redirection(token);
		else if (token->type == AND)
			ft_fix_other_operators(token);
		else if (token->type == PIPELINE)
			ft_fix_other_operators(token);
		else if (token->type == OR)
			ft_fix_other_operators(token);
	}
}

void	ft_browse_list(t_list **start)
{
	t_token	*token;

	while (start && *start)
	{
		token = (*start)->content;
		if (token->type != ESPACE)
		{
			ft_find_full_token(start, ft_find_type((*start)->content));
			ft_fix_syntax((*start)->content);
		}
		*start = (*start)->next;
	}
}
