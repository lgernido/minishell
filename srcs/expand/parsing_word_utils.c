/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_word_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:46:52 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/15 17:46:52 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "expand.h"
#include <stdlib.h>

static t_bool	is_valid_quote(char *quote_to_check)
{
	t_bool	return_value;

	return_value = TRUE;
	if (quote_to_check[0] == quote_to_check[1])
	{
		return_value = FALSE;
	}
	return (return_value);
}

t_bool	is_a_relevant_quote(int c, int flag)
{
	if (flag == 0 || flag == -1)
	{
		if (c == '"' || c == '\'')
		{
			return (TRUE);
		}
	}
	else
	{
		if (c == flag)
		{
			return (TRUE);
		}
	}
	return (FALSE);
}

void	update_current_quote(int *current_quote, int quote)
{
	if ((*current_quote == 0 || *current_quote == -1)
		&& (quote == '\'' || quote == '"'))
	{
		*current_quote = quote;
	}
	else
	{
		*current_quote = 0;
	}
	return ;
}

static char	*remove_irrelevant_quotes(char	*str, char *double_quote)
{
	char	*temp_str;

	double_quote[0] = 0;
	double_quote[1] = 0;
	temp_str = ft_strjoin(str, double_quote + 2);
	free(str);
	if (str == NULL)
	{
		return (NULL);
	}
	else
	{
		return (get_rid_of_double_quote(temp_str));
	}
}

char	*get_rid_of_double_quote(char *str)
{
	size_t	i;
	int		current_quote;

	current_quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (is_a_relevant_quote(str[i], current_quote) == TRUE)
		{
			if (is_valid_quote(&str[i]) == TRUE)
			{
				update_current_quote(&current_quote, str[i]);
			}
			else
			{
				return (remove_irrelevant_quotes(str, &str[i]));
			}
		}
		++i;
	}
	return (str);
}
