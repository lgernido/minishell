/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:58:49 by luciegernid       #+#    #+#             */
/*   Updated: 2024/02/13 10:03:05 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start_parse(t_core *minishell, char *str)
{
	char	*token;
	t_token	*tmp;

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
	//next ->parse tokens in commands
}
