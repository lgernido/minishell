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

int	setup_for_here_doc(t_core *minishell, t_token_stream_node*tmp)
{
	char	*delimiter;

	delimiter = NULL;
	tmp->next->type = T_LIM;
	delimiter = ft_strjoin(tmp->next->value, "\n");
	free(tmp->next->value);
	tmp->next->value = NULL;
	if (delimiter == NULL)
	{
		ft_clean_exit(minishell, MALLOC);
	}
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
