/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:03:55 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/15 09:01:28 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokenize_redirections(t_core *minishell, char *str, t_token **start,
		int i)
{
	if (str[i] == '>' && str[i + 1] == '>')
	{
		ft_add_token_list(start, ft_create_priority_token(minishell, ">>"));
		return (i + 2);
	}
	else if (str[i] == '<' && str[i + 1] == '<')
	{
		ft_add_token_list(start, ft_create_priority_token(minishell, "<<"));
		return (i + 2);
	}
	else if (str[i] == '<')
	{
		ft_add_token_list(start, ft_create_priority_token(minishell, "<"));
		return (i + 1);
	}
	else if (str[i] == '>')
	{
		ft_add_token_list(start, ft_create_priority_token(minishell, ">"));
		return (i + 1);
	}
	else
		return (i);
}
