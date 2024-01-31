/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <vlevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:03:27 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/25 17:38:11 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_str(char *stash, char *str, t_clist *lst, int lst_size)
{
	t_clist		*temp_node;
	int			len;

	temp_node = lst;
	len = ft_strlen_cs(stash, '\n', 1);
	ft_strncat(str, stash, len + 1);
	if (temp_node != NULL)
	{
		while (--lst_size)
		{
			ft_strncat(str, temp_node->content, BUFFER_SIZE + 1);
			temp_node = temp_node->next;
		}
		len = ft_strlen_cs(temp_node->content, '\n', 1);
		ft_strncat(str, temp_node->content, len + 1);
	}
	if (!update_stash(stash, temp_node))
	{
		free(str);
		str = NULL;
	}
	return (str);
}

char	*update_stash(char *stash, t_clist *temp_str_node)
{
	char	*temp_str;
	int		len_to_trim;

	temp_str = malloc(BUFFER_SIZE + 1 * sizeof (char));
	if (temp_str == NULL)
		return (NULL);
	if (temp_str_node != NULL)
	{
		ft_memset(stash, 0, BUFFER_SIZE + 1);
		len_to_trim = ft_strlen_cs(temp_str_node->content, '\n', 1);
		ft_strncat(stash, temp_str_node->content + len_to_trim, (BUFFER_SIZE
				- len_to_trim + 1));
	}
	else
	{
		ft_memset(temp_str, 0, BUFFER_SIZE + 1);
		len_to_trim = ft_strlen_cs(stash, '\n', 1);
		ft_strncat(temp_str, stash + len_to_trim, BUFFER_SIZE
			- len_to_trim + 1);
		ft_memset(stash, 0, BUFFER_SIZE + 1);
		ft_strncat(stash, temp_str, BUFFER_SIZE + 1);
	}
	free(temp_str);
	return (stash);
}

char	*handle_eol(int lst_size, char *stash, t_clist *lst)
{
	t_clist		*tmp;
	char		*str;
	int			i;
	int			len;

	i = 0;
	tmp = lst;
	if (tmp != NULL)
	{
		while (tmp->next)
			tmp = tmp->next;
		i = ft_strlen_cs(tmp->content, '\n', 1);
	}
	len = ft_strlen_cs(stash, '\n', 1) + i + ((lst_size - 1) * BUFFER_SIZE);
	if (len == 0)
		return (ft_lst_clear(&lst));
	str = malloc((len + 1) * sizeof (char));
	if (str == NULL)
		return (ft_lst_clear(&lst));
	ft_memset(str, 0, len + 1);
	str = fill_str(stash, str, lst, lst_size);
	ft_lst_clear(&lst);
	return (str);
}

char	*read_till_eol(char *str, char *stash, t_clist *lst, int fd)
{
	int		lst_size;
	char	*buff;

	buff = malloc(BUFFER_SIZE + 1 * sizeof (char));
	if (buff == NULL)
		return (NULL);
	lst_size = 0;
	ft_memset(buff, 0, BUFFER_SIZE + 1);
	while (BUFFER_SIZE == read(fd, buff, BUFFER_SIZE)
		&& ft_strlen_cs(buff, '\n', 0) == BUFFER_SIZE)
	{
		if (update_lst(&lst, buff))
			return (ft_lst_clear(&lst));
		lst_size++;
		ft_memset(buff, 0, BUFFER_SIZE + 1);
	}
	if (update_lst(&lst, buff))
		return (ft_lst_clear(&lst));
	lst_size++;
	str = handle_eol(lst_size, stash, lst);
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char						*str;
	static char					stash[FD_CAP][BUFFER_SIZE + 1];
	t_clist						*lst;
	int							stash_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = NULL;
	lst = NULL;
	stash_len = ft_strlen_cs(stash[fd], '\n', 0);
	if (*(stash[fd] + stash_len) == '\n')
		str = handle_eol(1, stash[fd], lst);
	else
		str = read_till_eol(str, stash[fd], lst, fd);
	return (str);
}
