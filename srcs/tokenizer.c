/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:21:00 by lgernido          #+#    #+#             */
/*   Updated: 2024/02/06 11:51:09 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_define_tokens(void)
{
	t_token token_list[] = {
		{"&", AND, NULL},
		{"<", SIMPLE_REDIR_LEFT, NULL},
		{">", SIMPLE_REDIR_RIGHT, NULL},
		{"<<", DOUBLE_REDIR_LEFT, NULL},
		{">>", DOUBLE_REDIR_RIGHT, NULL},
		{"|", PIPELINE, NULL},
		{"-", OPTION, NULL},
		{"\'", SINGLE_QUOTE, NULL},
		{"\"", DOUBLE_QUOTE, NULL},
		{"$", VARIABLE, NULL},
		{"\f", ESPACE, NULL},
		{"\n", ESPACE, NULL},
		{"\r", ESPACE, NULL},
		{"\t", ESPACE, NULL},
		{"\v", ESPACE, NULL},
		{" ", ESPACE, NULL},
		{";", SEMICOLON, NULL},
		{"\\", BACKSLASH, NULL},
	};
	return (token_list);
}

void	ft_list_remove_current_node(t_token *to_del)
{
	t_token	*tmp;

	if (!to_del)
		return ;
	tmp = to_del->next;
	// free(to_del->value);
	free(to_del);
	to_del = NULL;
}

void	ft_token_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*lst || !lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ;
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
	token->next = NULL;
	return (token);
}

static t_token_type	ft_define_type(char charset, t_token *token_list)
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

t_token	**ft_find_full_token(t_token **start)
{
	t_token	*current;

	if (!start || !*start)
		return (NULL);
	current = *start;
	while (current && current->next)
	{
		if (current->type == current->next->type)
		{
			ft_merge_token(current, current->next, current->type);
			ft_list_remove_current_node(current->next);
			current->next = current->next->next;
		}
		else
			current = current->next;
	}
	return (start);
}

t_token	*ft_tokenizer(char *str)
{
	int				i;
	t_token			*head;
	t_token			*new_token;
	t_token_type	type;
	t_token			*current;

	head = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		type = ft_define_type(str[i], head);
		new_token = ft_create_token(&str[i], type);
		ft_token_back(&head, new_token);
		i++;
	}
	ft_find_full_token(&head);
	printf("Liste des tokens :\n");
	current = head;
	while (current)
	{
		printf("Token : %s\n", (char *)current->value);
		printf("Type : %d\n", current->type);
		current = current->next;
	}
	return (head);
}
