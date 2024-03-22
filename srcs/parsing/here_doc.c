/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:13:23 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/22 12:00:06 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_del_here_doc(void)
{
	if (access("here_doc", F_OK) == 0)
	{
		if (unlink("here_doc") == -1)
		{
			ft_putstr_fd("Error: Couldn't delete here_doc\n", 2);
			return (-1);
		}
	}
	return (0);
}

static void	ft_here_doc_loop(char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
}

static void	ft_create_here_doc(t_core *minishell, char *delimiter)
{
	int	fd;

	ft_del_here_doc();
	fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Couldn't create here_doc\n", 2);
		ft_clear_token_list(&minishell->token_list);
		return ;
	}
	ft_here_doc_loop(delimiter, fd);
}

void	ft_here_doc(t_core *minishell)
{
	char	*delimiter;
	t_token	*tmp;

	delimiter = NULL;
	tmp = minishell->token_list;
	while (tmp->next != NULL)
	{
		if (tmp->type == T_HEREDOC)
		{
			tmp->next->type = T_LIM;
			delimiter = tmp->next->value;
			ft_create_here_doc(minishell, delimiter);
		}
		tmp = tmp->next;
	}
}
