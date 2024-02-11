/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciegernidos <luciegernidos@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:58:49 by luciegernid       #+#    #+#             */
/*   Updated: 2024/02/11 16:44:21 by luciegernid      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_define_type(t_token *tmp)
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

void	ft_start_parse(t_core *minishell, char *str)
{
	char	*token;
	t_token *tmp;

	if (!ft_is_ascii(str))
	{
		ft_dprintf(2, "minishell: invalid ascii characters found in string\n");
		return ;
	}
	ft_split_tokens(minishell, str);
	token = ft_tokenizer(minishell);
	if (token)
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n", token);
		return ;
	}
	tmp = minishell->token_list;
	while (tmp)
	//next ->parse tokens in comands
}

