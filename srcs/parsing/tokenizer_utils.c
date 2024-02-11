/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciegernidos <luciegernidos@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:42:14 by luciegernid       #+#    #+#             */
/*   Updated: 2024/02/11 17:04:10 by luciegernid      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_add_token_list(t_token **begin, t_token *new)
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

int			ft_token_list_size(t_token **begin)
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

void		ft_clear_token_list(t_token **begin, void (*del)(void *))
{
	t_token	*tmp;
	t_token *tmp2;

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

t_token		*ft_create_token(t_core *minishell, int i)
{
	t_token	*new;

	if (!minishell->count)
		return (NULL);
	if (!(new = ft_calloc(1, sizeof(t_token))))
		exit_cmd(minishell);
	new->value = ft_substr(minishell->user_input, i - minishell->count,
		minishell->count);
	minishell->count = 0;
	return (new);
}

t_token		*ft_create_arg_token(char *word, int type)
{
	t_token	*new;

	if (!(new = ft_calloc(1, sizeof(t_token))))
		ft_clean_exit(core, 1);
	new->value = ft_strdup(word);
	new->type = type;
	return (new);
}