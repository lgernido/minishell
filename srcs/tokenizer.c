/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:21:00 by lgernido          #+#    #+#             */
/*   Updated: 2024/02/05 15:04:48 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

typedef enum e_token_type
{
	AND,
	OR,
	SIMPLE_REDIR_LEFT,
	SIMPLE_REDIR_RIGHT,
	DOUBLE_REDIR_LEFT,
	DOUBLE_REDIR_RIGHT,
	PIPELINE,
	OPTION,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	LITERAL,
	VARIABLE,
	ESPACE,
	SEMICOLON,
	BACKSLASH,
	OPEN_PAR,
	CLOSE_PAR,
}					t_token_type;
typedef struct s_token
{
	void			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

static t_token		g_token_list[] = {
	{"&", AND},
	{"<", SIMPLE_REDIR_LEFT},
	{">", SIMPLE_REDIR_RIGHT},
	{"<<", DOUBLE_REDIR_LEFT},
	{">>", DOUBLE_REDIR_RIGHT},
	{"|", PIPELINE},
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
	{";", SEMICOLON},
	{"\\", BACKSLASH},
};

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (ft_strlen(src));
}
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*str;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	str = malloc(len + 1 * sizeof(char));
	if (str != NULL)
		ft_strlcpy(str, s, len + 1);
	return (str);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1[j] != 0)
		res[i++] = s1[j++];
	j = 0;
	while (s2[j] != 0)
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
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

static t_token_type	ft_define_type(char charset)
{
	int				i;
	char			*str;
	t_token_type	type;

	i = 0;
	type = LITERAL;
	while (g_token_list[i].value)
	{
		str = g_token_list[i].value;
		if (str[0] == charset)
		{
			type = g_token_list[i].type;
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
	t_token			*token_list;
	t_token			**new_list;
	t_token			*new_token;
	t_token_type	type;

	i = 0;
	new_token = NULL;
	token_list = NULL;
	while (str[i] != '\0')
	{
		type = ft_define_type(str[i]);
		new_token = ft_create_token(&str[i], type);
		ft_token_back(&token_list, new_token);
		i++;
	}
	new_list = ft_find_full_token(&token_list);
	return (*new_list);
}

int	main(int argc, char **argv)
{
	t_token	*tokens;
	t_token	*temp;

	(void)argc;
	tokens = ft_tokenizer(argv[1]);
	while (tokens != NULL)
	{
		printf("Value: %s |||| Type: %d\n", (char *)tokens->value,
			tokens->type);
		tokens = tokens->next;
	}
	// while (tokens != NULL)
	// {.
	// 	temp = tokens;
	// 	tokens = tokens->next;
	// 	free(temp->value);
	// 	free(temp);
	// }
	return (0);
}
