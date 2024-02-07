/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:21:00 by lgernido          #+#    #+#             */
/*   Updated: 2024/02/07 10:51:01 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token		token_list[] = {
	{"&", AND},
	{"|", PIPELINE},
	{"<", SIMPLE_REDIR_LEFT},
	{">", SIMPLE_REDIR_RIGHT},
	{";", SEMICOLON},
	{"-", OPTION},
	{"\'", SINGLE_QUOTE},
	{"\"", DOUBLE_QUOTE},
	{"$", VARIABLE},
	{"\f", ESPACE},
	{"\n", ESPACE},
	{"\r", ESPACE},
	{"\t", ESPACE},
	{"\v", ESPACE},
	{" ", ESPACE},
	{"\\", BACKSLASH},
};

t_token_type	ft_find_type(t_token *token)
{
	return (token->type);
}

void	ft_clear_token(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = (t_token *)content;
	if (token && token->value)
		free(token->value);
	free(token);
	(void)content;
	(void)token;
}

t_token	*ft_create_token(void *token_value, t_token_type token_type)
{
	t_token	*token;
	int		size;

	size = sizeof(t_token);
	token = malloc(size);
	if (!token || !token_value)
		return (NULL);
	token->value = token_value;
	token->type = token_type;
	;
	return (token);
}

static t_token_type	ft_define_type(char charset)
{
	int				i;
	char			*str;
	t_token_type	type;

	i = 0;
	type = LITERAL;
	while (token_list[i].value)
	{
		str = token_list[i].value;
		if (str[0] == charset)
		{
			type = token_list[i].type;
			return (type);
		}
		i++;
	}
	return (type);
}

static t_token	*ft_merge_token(t_token *token_1, t_token *token_2,
		t_token_type type)
{
	char	*token1_value;
	char	*token2_value;
	char	*join;
	t_token	*token;

	token1_value = (char *)token_1->value;
	token2_value = (char *)token_2->value;
	join = ft_strjoin(token1_value, token2_value);
	if (!join)
		return (NULL);
	token = ft_create_token((void *)join, type);
	if (!token)
	{
		free(join);
		return (NULL);
	}
	return (token);
}

void	ft_find_full_token(t_list **start, t_token_type type)
{
	t_token	*temp;
	t_list	*rm;

	while (start && *start && (*start)->next)
	{
		if (ft_find_type((*start)->content) != type)
			return ;
		if (ft_find_type((*start)->next->content) != type)
			return ;
		temp = (*start)->next->content;
		temp = ft_merge_token((*start)->content, temp, type);
		rm = *start;
		*start = rm->next;
		ft_clear_token((*start)->content);
		(*start)->content = temp;
		free(rm);
	}
}

void	ft_tokenizer(char *str)
{
	t_list *list;
	char *value;
	t_token *token;
	t_token_type type;

	value = ft_strdup(str);
	if (!value)
		return ;
	type = ft_define_type(value[0]);
	token = ft_create_token(value, type);
	if (!(list = ft_lstnew(token)))
	{
		free(value);
		return ;
	}
	ft_lstadd_back(&list, list);
}