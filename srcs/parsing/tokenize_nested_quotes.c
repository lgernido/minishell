/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_nested_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:39:28 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/22 18:39:29 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_a_meta_character(char c)
{
	const char	meta_characters[] = "<>|&()";
	size_t		i;

	i = 0;
	while (meta_characters[i] != '\0')
	{
		if (c == meta_characters[i])
		{
			return (TRUE);
		}
		++i;
	}
	return (FALSE);
}

static void	update_flag(int *flag, char quote_to_check)
{
	if (*flag == 0)
	{
		*flag = quote_to_check;
	}
	else if (*flag == quote_to_check)
	{
		*flag = 0;
	}
	return ;
}

static	size_t	get_end_of_token(char *str, size_t i)
{
	int				flag;

	flag = 0;
	while (str[i] != '\0')
	{	
		if (str[i] == '\"' || str[i] == '\'')
		{
			update_flag(&flag, str[i]);
		}
		if (flag == 0 && (is_a_meta_character(str[i]) == TRUE
				|| ft_is_space(str[i]) == 1))
		{
			break ;
		}
		++i;
	}
	return (i);
}

static t_token	*ft_create_nested_token(t_core *minishell, int i, char *str)
{
	t_token	*new;
	int		token_len;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		ft_clean_exit(minishell, MALLOC);
	token_len = 0;
	while (str[i + token_len] != '\0')
	{
		token_len++;
	}
	new->value = ft_substr(str, i, token_len);
	return (new);
}

int	tokenize_nested_quotes(t_core *minishell, char *str,
		t_token **start, size_t i)
{
	const size_t	token_start = i;
	const size_t	end_of_token = get_end_of_token(str, i);
	const char		ending_char = str[end_of_token];
	t_token			*new_token;

	str[end_of_token] = '\0';
	new_token = ft_create_nested_token(minishell, token_start, str);
	ft_add_token_list(start, new_token);
	str[end_of_token] = ending_char;
	return (end_of_token);
}
