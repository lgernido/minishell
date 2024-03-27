/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:42:30 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/22 17:42:31 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quote_is_relevant(int *flag, int quote_to_check)
{
	int	return_value;

	return_value = 0;
	if (*flag == 0)
	{
		*flag = quote_to_check;
		return_value = 1;
	}
	else if (*flag == quote_to_check)
	{
		*flag = 0;
		return_value = 1;
	}
	return (return_value);
}

static t_bool	is_a_full_quoted_token(char *str, int i)
{
	const char	quote_type = str[i];
	const int	j = i + 1;
	t_bool		return_value;

	return_value = FALSE;
	++i;
	while (str[i] != quote_type)
	{
		++i;
	}
	if ((str[i + 1] == '\0' || ft_is_space(str[i + 1])) && i != j)
	{
		return_value = TRUE;
	}
	return (return_value);
}

int	ft_handle_quoted_token(t_core *minishell, char *str,
		t_token_stream_node **start, int i)
{
	const t_bool	is_simply_quoted = is_a_full_quoted_token(str, i);
	int				index_to_return;

	if (is_simply_quoted == TRUE)
	{
		index_to_return = ft_tokenize_quotes(minishell, str, start, i);
	}
	else
	{
		index_to_return = tokenize_nested_quotes(minishell, str, start, i);
	}
	return (index_to_return);
}

int	ft_quotes(char *str)
{
	int	i;
	int	flag;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	flag = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\"' && quote_is_relevant(&flag, str[i]) == 1)
			double_quotes++;
		else if (str[i] == '\'' && quote_is_relevant(&flag, str[i]) == 1)
			single_quotes++;
		i++;
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		return (1);
	else
		return (0);
}
