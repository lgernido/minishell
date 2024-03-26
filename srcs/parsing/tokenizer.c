/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:21:00 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/22 15:59:39 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structures_define_and_includes.h"
#include "minishell.h"

int	ft_define_type(t_token_stream_node*tmp)
{
	if (ft_samestr(tmp->value, "||"))
		tmp->type = T_OR;
	else if (ft_samestr(tmp->value, ";"))
		tmp->type = T_SEP;
	else if (ft_samestr(tmp->value, "&&"))
		tmp->type = T_AND;
	else if (ft_samestr(tmp->value, "|"))
		tmp->type = T_PIPE;
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

int	ft_fix_redirect_types(t_token_stream_node token_to_fix)
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

char	*check_abstract_syntax(t_core *minishell)
{
	t_token_stream_node	*tmp;

	tmp = minishell->token_list;
	while (tmp->next != NULL)
	{
		if (tmp->type != T_DOUBLE_QUOTES && tmp->type != T_SIMPLE_QUOTES)
		{
			if (ft_check_error(tmp) || ft_parenthesis_check(tmp))
				return (tmp->value);
			else
				tmp->type = ft_fix_redirect_types(*tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_tokenizer(t_core *minishell)
{
	t_token_stream_node	*tmp;

	tmp = minishell->token_list;
	while (tmp->next != NULL)
	{
		if (tmp->type != T_DOUBLE_QUOTES && tmp->type != T_SIMPLE_QUOTES)
		{
			if (ft_samestr(tmp->value, ">") || ft_samestr(tmp->value, ">>")
				|| ft_samestr(tmp->value, "<<") || ft_samestr(tmp->value, "<"))
				tmp->type = T_REDIRECT;
			else if (ft_define_type(tmp))
				;
			else if (!tmp->type)
				tmp->type = T_WORD;
		}
		tmp = tmp->next;
	}
	return (check_abstract_syntax(minishell));
}
