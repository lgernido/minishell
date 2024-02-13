/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:21:00 by lgernido          #+#    #+#             */
/*   Updated: 2024/02/13 10:30:25 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
i = character's position in the array
str = array to analyze
sep = separator
sign = handling context
	0 -> check if c[i] and c[i - 1] == sep
	1 -> check if c[i] == sep and c[i + 1] != sep
	2 -> same as 0 but with c[i + 1]
	3 -> check if c[i] == sep
*/

int	ft_split_utils(int i, char *str, char *sep, int sign)
{
	if (sign == 1 && ft_find_char_str(str[i], sep) && !ft_find_char_str(str[i
			+ 1], sep) && !ft_quotes(str, i) && !ft_escape(str, i - 1))
		return (1);
	else if (!sign && ft_find_char_str(str[i], sep) && i > 0
		&& ft_find_char_str(str[i - 1], sep) && !ft_quotes(str, i)
		&& !ft_escape(str, i - 1))
		return (1);
	else if (sign == 2 && ft_find_char_str(str[i], sep) && i > 0
		&& ft_find_char_str(str[i - 1], sep) && !ft_quotes(str, i)
		&& !ft_escape(str, i - 1))
		return (1);
	else if (sign == 3 && ft_find_char_str(str[i], sep) && !ft_quotes(str, i)
		&& !ft_escape(str, i - 1))
		return (1);
	return (0);
}

int	ft_split_tokens2(t_core *minishell, char *str, int *i, t_token **start)
{
	if (ft_find_char_str(str[*i], " \t") && !ft_quotes(str, *i)
		&& !ft_escape(str, *i - 1))
	{
		ft_add_token_list(start, ft_create_token(minishell, *i));
		(*i)++;
		return (0);
	}
	if ((ft_find_char_str(str[*i], "|;<>&()") && *i > 0
			&& !ft_find_char_str(str[*i - 1], "|;<>&()")) && !ft_quotes(str, *i)
		&& !ft_escape(str, *i - 1))
		ft_add_token_list(start, ft_create_token(minishell, *i));
	return (1);
}

void	ft_split_tokens(t_core *minishell, char *str)
{
	int		i;
	int		nb_token;
	t_token	**start;

	i = 0;
	start = &minishell->token_list;
	while (str[i])
	{
		if (!ft_split_tokens2(minishell, str, &i, start))
			continue ;
		if (ft_split_utils(i, str, "|", 1) || ft_split_utils(i, str, "|", 0)
			|| ft_split_utils(i, str, ">", 1) || ft_split_utils(i, str, ">", 0)
			|| ft_split_utils(i, str, "<", 1) || ft_split_utils(i, str, "<", 0)
			|| ft_split_utils(i, str, "&", 2) || ft_split_utils(i, str, ";()",
				3))
			ft_add_token_list(start, ft_create_token(minishell, i + 1));
		i++;
	}
	if (i > 0)
	{
		ft_add_token_list(&minishell->token_list, ft_create_token(minishell,
				i));
		ft_add_token_list(&minishell->token_list, ft_create_arg_token("newline",
				T_NEWLINE));
	}
}

int	ft_check_error(t_token *token)
{
	if ((token->type == T_PIPE || token->type == T_SEP || token->type == T_AND
			|| token->type == T_OR) && !token->prev)
		return (0);
	if (token->type == T_REDIRECT && (token->prev
			&& token->prev->type == T_REDIRECT))
		return (0);
	if (token->type == T_NEWLINE && token->prev
		&& (token->prev->type == T_REDIRECT || token->prev->type == T_PIPE
			|| token->prev->type == T_AND || token->prev->type == T_OR))
		return (0);
	if ((token->type == T_PIPE || token->type == T_SEP || token->type == T_AND
			|| token->type == T_OR) && (token->prev->type == T_PIPE
			|| token->prev->type == T_SEP || token->prev->type == T_REDIRECT
			|| token->prev->type == T_AND || token->prev->type == T_OR))
		return (0);
	return (1);
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
		if (!ft_check_error(tmp))
		{
			ft_fixe_redirect_types(tmp);
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_fixe_redirect_types(t_token token_to_fix)
{
	if (ft_samestr(token_to_fix->value, ">"))
		tmp->type = T_OUTPUT_FILE;
	else if (ft_samestr(token_to_fix->value, ">>"))
		tmp->type = T_APPEND;
	else if (ft_samestr(token_to_fix->value, "<"))
		tmp->type = T_INPUT_FILE;
	else if (ft_samestr(token_to_fix->value = "<<"))
		tmp->type = T_HEREDOC;
}
