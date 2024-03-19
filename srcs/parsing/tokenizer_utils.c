/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:42:14 by luciegernid       #+#    #+#             */
/*   Updated: 2024/03/19 13:20:05 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_token_list(t_token **begin, t_token *new)
{
	t_token	*tmp;

	if (!new || !begin)
		return ;
	if (*begin)
	{
		tmp = *begin;
		while (tmp->next)
		{
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
		*begin = new;
}

void	ft_clear_token_list(t_token **begin, void (*del)(void *))
{
	t_token	*tmp;
	t_token	*tmp2;

	if (!begin || !del)
		return ;
	tmp = *begin;
	while (tmp)
	{
		ft_strdel(&tmp->value);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*begin = NULL;
}

t_token	*ft_create_token(t_core *minishell, int i, char *str)
{
	t_token	*new;
	int		token_len;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		ft_clean_exit(minishell, MALLOC);
	token_len = 0;
	while (str[i + token_len] != '\0' && !ft_is_separator(str[i + token_len]))
	{
		token_len++;
	}
	new->value = ft_substr(str, i, token_len);
	return (new);
}

t_token	*ft_create_priority_token(t_core *minishell, char *str)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		ft_clean_exit(minishell, MALLOC);
	new->value = str;
	return (new);
}

t_token	*ft_create_arg_token(t_core *minishell, char *word, int type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		ft_clean_exit(minishell, MALLOC);
	new->value = ft_strdup(word);
	new->type = type;
	return (new);
}
