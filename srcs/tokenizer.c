/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:21:00 by lgernido          #+#    #+#             */
/*   Updated: 2024/01/31 10:35:42 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_tokenizer
{
	char			**source;
	char			*current_position;
	struct s_token	cur_token;
}					t_tokenizer;

typedef struct s_token
{
	char			*name;
	char			*value;
}					t_token;

static int	ft_ispunct(int c)
{
	if (!ft_isalnum(c))
		return (1);
	return (0);
}
static void	ft_protection(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	ft_get_word_count(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (ft_ispunct(str[i]) && str[i] != ' ')
			count++;
		else if (ft_isalnum(str[i]))
		{
			while (ft_isalnum(str[i]) && str[i] != ' ')
				i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}

static char	*ft_extract_word(char *str, int *index)
{
	int		k;
	char	*word;

	k = 0;
	while (ft_isalnum(str[*index]))
	{
		k++;
		(*index)++;
	}
	word = malloc(sizeof(char) * (k + 1));
	if (!word)
		return (NULL);
	*index -= k;
	k = 0;
	while (ft_isalnum(str[*index]) && str[*index] != ' ')
	{
		word[k++] = str[(*index)++];
	}
	word[k] = '\0';
	return (word);
}

char	**ft_split_punct(char *str)
{
	char	**tab;
	int		word_count;
	int		i;
	int		j;

	word_count = ft_get_word_count(str);
	tab = malloc(sizeof(char *) * (word_count + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_ispunct(str[i]) && str[i] != ' ')
		{
			tab[j] = ft_extract_word(str, &i);
			if (!tab[j])
				return (ft_protection(tab), NULL);
			j++;
			i++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}

t_token	*ft_tokenize_line(char *str)
{
	t_token		*token;
	t_tokenizer	tokenizer;
	char		**tab;
	int			i;

	i = 0;
	tab = ft_split_punct(str);
	if (!tab)
		return (NULL);
	token = malloc(sizeof(t_token) * (ft_tablen(tab) + 1));
	if (!token)
		return (ft_protection(tab), NULL);
	ft_init_tokenizer(tokenizer, tab);
	while (tab[i])
	{
		ft_get_next_token(&tokenizer);
		i++;
	}
	token[i].name = NULL;
	token[i].value = NULL;
	ft_protection(tab);
	return (token);
}

void	ft_init_tokenizer(struct tokenizer *tokenizer, char **source)
{
	tokenizer->source = source;
	tokenizer->current_position = source;
	ft_memset(&tokenizer->cur_token, 0, sizeof(struct token));
}

// Function to get the next token
void	ft_get_next_token(struct tokenizer *tokenizer)
{
	char	number[20];
	char	operator;
	int		i;

	// Skip leading whitespace
	while (ft_isspace(*tokenizer->current_position))
		tokenizer->current_position++;
	if (ft_isdigit(*tokenizer->current_position))
	{
		// Read a number
		i = 0;
		while (ft_isdigit(*tokenizer->current_position) && i < 19)
			number[i++] = *tokenizer->current_position++;
		number[i] = '\0';
		ft_strcpy(tokenizer->cur_token.name, "NUMBER");
		ft_strcpy(tokenizer->cur_token.value, number);
	}
	else if (*tokenizer->current_position == '('
		|| *tokenizer->current_position == ')')
	{
		// Read parentheses
		if (*tokenizer->current_position == '(')
			ft_strcpy(tokenizer->cur_token.name, "LEFTPAREN");
		else
			ft_strcpy(tokenizer->cur_token.name, "RIGHTPAREN");
		tokenizer->cur_token.value[0] = *tokenizer->current_position++;
		tokenizer->cur_token.value[1] = '\0';
	}
	else if (*tokenizer->current_position != '\0')
	{
		// Read an operator
		ft_strcpy(tokenizer->cur_token.name, "BINOP");
		tokenizer->cur_token.value[0] = *tokenizer->current_position++;
		tokenizer->cur_token.value[1] = '\0';
	}
	else
		ft_memset(&tokenizer->cur_token, 0, sizeof(struct token));
}
