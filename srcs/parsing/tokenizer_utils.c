/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:42:14 by luciegernid       #+#    #+#             */
/*   Updated: 2024/03/21 13:04:56 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "clean_and_error.h"

void	ft_add_token_list(t_token_stream_node **begin, t_token_stream_node *new)
{
	t_token_stream_node	*tmp;

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

void	ft_clear_token_list(t_token_stream_node **begin)
{
	t_token_stream_node	*tmp;
	t_token_stream_node	*tmp2;

	if (!begin)
		return ;
	tmp = *begin;
	while (tmp)
	{
		tmp2 = tmp->next;
		ft_strdel(&tmp->value);
		free(tmp);
		tmp = tmp2;
	}
	*begin = NULL;
}

t_token_stream_node	*ft_create_token(t_core *minishell, int i, char *str)
{
	t_token_stream_node	*new;
	int					token_len;

	new = ft_calloc(1, sizeof(t_token_stream_node));
	if (!new)
		exit_from_parsing(minishell, str, MALLOC);
	token_len = 0;
	while (str[i + token_len] != '\0' && !ft_is_separator(str[i + token_len]))
	{
		token_len++;
	}
	new->value = ft_substr(str, i, token_len);
	if (new->value == NULL)
		exit_from_parsing(minishell, str, MALLOC);
	return (new);
}

t_token_stream_node	*ft_create_priority_token(t_core *minishell,
		const char *token, char *str)
{
	t_token_stream_node	*new;

	new = ft_calloc(1, sizeof(t_token_stream_node));
	if (!new)
		exit_from_parsing(minishell, str, MALLOC);
	new->value = ft_strdup(token);
	if (new->value == NULL)
		exit_from_parsing(minishell, str, MALLOC);
	return (new);
}

t_token_stream_node	*ft_create_arg_token(t_core *minishell, char *word,
		int type, char *str)
{
	t_token_stream_node	*new;

	new = ft_calloc(1, sizeof(t_token_stream_node));
	if (!new)
		ft_clean_exit(minishell, MALLOC);
	new->value = ft_strdup(word);
	if (new->value == NULL)
		exit_from_parsing(minishell, str, MALLOC);
	new->type = type;
	return (new);
}
