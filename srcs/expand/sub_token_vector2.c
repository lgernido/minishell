/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_token_vector2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:41:03 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/18 16:41:05 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_vector(t_sub_token_vector *src, t_sub_token **dest)
{
	size_t	i;

	i = 0;
	while (i < src->vector_size)
	{
		dest[i] = src->sub_token_list[i];
		src->sub_token_list[i] = NULL;
		++i;
	}
}

static int	realloc_vector(t_core *core)
{
	t_sub_token	**temp_vector;

	temp_vector = ft_calloc(2 * core->sub_token_vector->vector_size,
			sizeof(t_sub_token));
	if (temp_vector == NULL)
	{
		return (-1);
	}
	copy_vector(core->sub_token_vector, temp_vector);
	ft_clean_sub_token_list(core->sub_token_vector->sub_token_list,
		core->sub_token_vector->vector_size);
	core->sub_token_vector->sub_token_list = temp_vector;
	core->sub_token_vector->vector_size *= 2;
	return (0);
}

int	update_iterator_position(t_core *core)
{
	int	return_value;

	return_value = -1;
	if (core->sub_token_vector->iterator + 1
		== core->sub_token_vector->vector_size)
	{
		return_value = realloc_vector(core);
	}
	core->sub_token_vector->iterator += 1;
	return (return_value);
}

char	*ft_strndup(char *start, char *end)
{
	const size_t	len = end - start + 1;
	char			*dest;

	dest = ft_calloc(len + 1, sizeof(char));
	if (dest == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(dest, start, len + 1);
	return (dest);
}
