/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:42:14 by luciegernid       #+#    #+#             */
/*   Updated: 2024/02/14 09:20:49 by lgernido         ###   ########.fr       */
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

int	ft_token_list_size(t_token **begin)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = *begin;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
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
		free(&tmp->value);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*begin = NULL;
}

t_token	*ft_create_token(t_core *minishell, int i, char *str)
{
	t_token	*new;
	int		token_length;

	if (!(new = ft_calloc(1, sizeof(t_token))))
		ft_clean_exit(minishell);
	token_length = 0;
	while (str[i + token_length] != '\0' && !ft_is_separator(str[i
			+ token_length]))
	{
		token_length++;
	}
	new->value = ft_substr(str, i, token_length);
	return (new);
}

t_token	*ft_create_arg_token(char *word, int type)
{
	t_token *new;

	if (!(new = ft_calloc(1, sizeof(t_token))))
		ft_clean_exit(core, 1);
	new->value = ft_strdup(word);
	new->type = type;
	return (new);
}