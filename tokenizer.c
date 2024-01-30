/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:21:00 by lgernido          #+#    #+#             */
/*   Updated: 2024/01/30 14:37:31 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../libft/libft.h"
//#include "token.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}

int	ft_ispunct(int c)
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

char	**ft_split_punct(char *str)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	tab = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_ispunct(str[i]) && str[i] != ' ')
		{
			tab[j] = malloc(sizeof(char) * 2);
			if (!tab[j])
			{
				ft_protection(tab);
				return (NULL);
			}
			tab[j][0] = str[i];
			tab[j][1] = '\0';
			j++;
			i++;
		}
		else if (ft_isalnum(str[i]))
		{
			k = 0;
			while (ft_isalnum(str[i + k]))
				k++;
			tab[j] = malloc(sizeof(char) * (k + 1));
			if (!tab[j])
			{
				ft_protection(tab);
				return (NULL);
			}
			k = 0;
			while (ft_isalnum(str[i]) && str[i] != ' ')
			{
				tab[j][k] = str[i];
				k++;
				i++;
			}
			tab[j][k] = '\0';
			j++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}

int	main(int argc, char **argv)
{
	char	**tab;
	int		i;

	if (argc == 2)
	{
		tab = ft_split_punct(argv[1]);
		if (!tab)
			return (1);
		i = 0;
		while (tab[i])
		{
			printf("%s\n", tab[i]);
			i++;
		}
	}
	return (0);
}


void	ft_init_tokenizer(struct tokenizer *tokenizer, char *source)
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

int	main(void)
{
	char				source[] = "42 + (17 - 5)";
	struct tokenizer	tokenizer;

	// Example usage
	ft_init_tokenizer(&tokenizer, source);
	while (ft_strlen(tokenizer.cur_token.name) > 0)
	{
		ft_get_next_token(&tokenizer);
		printf("token: %s, Value: %s\n", tokenizer.cur_token.name,
			tokenizer.cur_token.value);
	}
	return (0);
}
