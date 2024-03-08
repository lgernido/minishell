/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:21:00 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/08 12:51:07 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_error(t_token *token)
{
	if ((token->type == T_PIPE || token->type == T_SEP || token->type == T_AND
			|| token->type == T_OR) && !token->prev)
		return (1);
	if (token->type == T_REDIRECT && (token->prev
			&& token->prev->type == T_REDIRECT))
		return (1);
	if (token->type == T_NEWLINE && token->prev
		&& (token->prev->type == T_REDIRECT || token->prev->type == T_PIPE
			|| token->prev->type == T_AND || token->prev->type == T_OR))
		return (1);
	if ((token->type == T_PIPE || token->type == T_SEP || token->type == T_AND
			|| token->type == T_OR) && (token->prev->type == T_PIPE
			|| token->prev->type == T_SEP || token->prev->type == T_REDIRECT
			|| token->prev->type == T_AND || token->prev->type == T_OR))
		return (1);
	if ((token->type == T_REDIRECT && token->next->type == T_NEWLINE))
		return (1);
	return (0);
}
int	ft_define_type(t_token *tmp)
{
	if (ft_samestr(tmp->value, "|"))
		tmp->type = T_PIPE;
	else if (ft_samestr(tmp->value, ";"))
		tmp->type = T_SEP;
	else if (ft_samestr(tmp->value, "&&"))
		tmp->type = T_AND;
	else if (ft_samestr(tmp->value, "||"))
		tmp->type = T_OR;
	else if (ft_samestr(tmp->value, "("))
		tmp->type = T_PAR_OPEN;
	else if (ft_samestr(tmp->value, ")"))
		tmp->type = T_PAR_CLOSE;
	else if (ft_samestr(tmp->value, "newline") && !tmp->next)
		tmp->type = T_NEWLINE;
	else
		return (0);
	return (1);
}

int	ft_fix_redirect_types(t_token token_to_fix)
{
	if (ft_samestr(token_to_fix.value, ">"))
		return (T_OUTPUT_FILE);
	else if (ft_samestr(token_to_fix.value, ">>"))
		return (T_APPEND);
	else if (ft_samestr(token_to_fix.value, "<"))
		return (T_INPUT_FILE);
	else if (ft_samestr(token_to_fix.value, "<<"))
		return (T_HEREDOC);
	else
		return (token_to_fix.type);
}
char	*ft_tokenizer(t_core *minishell)
{
	t_token	*tmp;

	tmp = minishell->token_list;
	while (tmp)
	{
		if (ft_samestr(tmp->value, ">") || ft_samestr(tmp->value, ">>")
			|| ft_samestr(tmp->value, "<<") || ft_samestr(tmp->value, "<"))
			tmp->type = T_REDIRECT;
		else if (ft_define_type(tmp))
			;
		else
			tmp->type = T_WORD;
		tmp = tmp->next;
	}
	tmp = minishell->token_list;
	while (tmp)
	{
		if (ft_check_error(tmp))
			return (tmp->value);
		else
			tmp->type = ft_fix_redirect_types(*tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
