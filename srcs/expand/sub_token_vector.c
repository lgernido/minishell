/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_token_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:19:26 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/15 16:19:29 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

void	init_vector(t_core *core)
{
	core->sub_token_vector = ft_calloc(1, sizeof(t_sub_token_vector));
	if (core->sub_token_vector == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	core->sub_token_vector->sub_token_list = ft_calloc(4, sizeof(t_sub_token));
	if (core->sub_token_vector->sub_token_list == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	core->sub_token_vector->vector_size = 4;
}

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

static void	realloc_vector(t_core *core)
{
	t_sub_token	**temp_vector;

	temp_vector = ft_calloc(2 * core->sub_token_vector->vector_size,
			sizeof(t_sub_token));
	if (temp_vector == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	copy_vector(core->sub_token_vector, temp_vector);
	ft_clean_sub_token_list(core->sub_token_vector->sub_token_list,
		core->sub_token_vector->vector_size);
	core->sub_token_vector->sub_token_list = temp_vector;
}

void	update_iterator_position(t_core *core)
{
	if (core->sub_token_vector->iterator + 1
		== core->sub_token_vector->vector_size)
	{
		realloc_vector(core);
	}
	core->sub_token_vector->iterator += 1;
	return ;
}

char	*ft_strndup(char *start, char *end)
{
	const size_t	len = end - start;
	char			*dest;

	dest = ft_calloc(len + 1, sizeof(char));
	if (dest == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(dest, start, len + 1);
	return (dest);
}

void	create_new_sub_token(t_core *core, char *new_token_start,
		char *new_token_end, t_subtypes type)
{
	t_sub_token	*token_to_create;

	update_iterator_position(core);
	token_to_create = core->sub_token_vector->sub_token_list
	[core->sub_token_vector->iterator];
	token_to_create = malloc(sizeof(t_sub_token));
	if (token_to_create == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	token_to_create->type = type;
	token_to_create->value = ft_strndup(new_token_start, new_token_end);
	if (token_to_create->value == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
}
