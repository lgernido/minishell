/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:21:00 by lgernido          #+#    #+#             */
/*   Updated: 2024/02/01 14:36:54 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"

typedef enum e_token_type
{
	and,
	or
	, simple_redir_left, simple_redir_right, double_redir_left,
		double_redir_right, pipeline, option, single_quote, double_quote,
		literal, variable, space, semicolon, backslash,
}					t_token_type;

typedef struct s_token
{
	void			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

static t_token		token_list[] = {
	{"&", and},
	{"|", pipeline},
	{"<<", double_redir_left},
	{">>", double_redir_right},
	{"<", simple_redir_left},
	{">", simple_redir_right},
	{";", semicolon},
	{"\"", double_quote},
	{"'", single_quote},
	{"\\", backslash},
	{"\f", space},
	{"\n", space},
	{"\r", space},
	{"\t", space},
	{"\v", space},
	{" ", space},
	{"$", variable},
	{"-", option},
};

void	ft_token_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*lst)
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
static t_token_type	define_type(char charset)
{
	int				i;
	char			*str;
	t_token_type	type;

	i = 0;
	type = literal;
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
t_token	*ft_tokenizer(char *str)
{
	int				i;
	t_token			*token_list;
	t_token			*new_token;
	t_token_type	type;

	i = 0;
	new_token = NULL;
	while (str[i])
	{
		type = define_type(str[i]);
		new_token = ft_create_token(&str[i], type);
		ft_token_back(&token_list, new_token);
		i++;
	}
	return (token_list);
}

int	main(int ac, char **av)
{
	t_token	*token_list;

	if (ac == 2)
	{
		token_list = ft_tokenizer(av[1]);
		while (token_list)
		{
			printf("token : %c\n", *(char *)token_list->value);
			printf("type : %d\n\n", token_list->type);
			token_list = token_list->next;
		}
	}
	return (0);
}
/*Suite : rassembler les tokens du meme types consecutifs
l = literal
s = literal
- = option
l = literal devient
ls = literal
- = option
l = literal*/