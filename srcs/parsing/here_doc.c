/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:13:23 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/25 16:27:22 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "clean_and_error.h"

void	copy_into_token(t_token_stream_node*tmp, char *line, int i)
{
	char	*buffer;

	if (i == 0)
		tmp->value = ft_strdup(line);
	else
	{
		buffer = ft_strjoin(tmp->value, line);
		if (tmp->value != NULL)
		{
			free(tmp->value);
		}
		tmp->value = buffer;
	}
}

void	ft_create_here_doc(t_token_stream_node*tmp, char *delimiter)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (g_signal == 130)
			break ;
		if (line == NULL)
		{
			ft_dprintf(2, "minishell: warning: here-document at line %d \
delimited by end-of-file (wanted `%s'\n", i, delimiter);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		copy_into_token(tmp, line, i);
		free(line);
		++i;
	}
}

char	*get_delimiter(t_core *minishell, char *token_value)
{
	char	*return_str;
	char	*tmp;

	parse_word_init(minishell, token_value);
	tmp = join_vector_in_a_string(minishell);
	ft_clean_sub_vector(&minishell->sub_token_vector);
	return_str = ft_strjoin(tmp, "\n");
	free(tmp);
	if (return_str == NULL)
	{
		ft_clean_exit(minishell, MALLOC);
	}
	return (return_str);
}

int	setup_for_here_doc(t_core *minishell, t_token_stream_node*tmp)
{
	char	*delimiter;

	delimiter = NULL;
	tmp->next->type = T_LIM;
	delimiter = get_delimiter(minishell, tmp->next->value);
	tmp->next->value = NULL;
	ft_create_here_doc(tmp->next, delimiter);
	free(delimiter);
	check_errno(minishell);
	if (tmp->next->value != NULL)
	{
		if (ft_strlen(tmp->next->value) > 65535)
		{
			ft_dprintf(2, "minishell: here_doc too big, risks\
					to cause a pipe overflow\n");
			return (1);
		}
	}
	return (0);
}

int	ft_here_doc(t_core *minishell)
{
	t_token_stream_node	*tmp;
	int					return_value;

	tmp = minishell->token_list;
	return_value = 0;
	while (tmp->next != NULL && g_signal != 130 && return_value == 0)
	{
		if (tmp->type == T_HEREDOC)
		{
			return_value = setup_for_here_doc(minishell, tmp);
		}
		tmp = tmp->next;
	}
	return (return_value);
}
