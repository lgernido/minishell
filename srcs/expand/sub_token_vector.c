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

#include "minishell.h"
#include "expand.h"

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

void	create_new_sub_token(t_core *core, char *new_token_start,
		char *new_token_end, t_subtypes type)
{
	t_sub_token	*token_to_create;

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
	core->sub_token_vector->sub_token_list[core->sub_token_vector->iterator]
		= token_to_create;
	update_iterator_position(core);
}

char	*join_vector_in_a_string(t_core *core)
{
	size_t	i;
	char	*str;
	char	*joined_str;

	i = 1;
	str = core->sub_token_vector->sub_token_list[0]->value;
	while (i < core->sub_token_vector->vector_size)
	{
		if (core->sub_token_vector->sub_token_list[i] != NULL)
		{
			joined_str = ft_strjoin(str,
					core->sub_token_vector->sub_token_list[i]->value);
			if (joined_str == NULL)
			{
				ft_clean_exit(core, MALLOC);
			}
			free(str);
			str = joined_str;
		}
		++i;
	}
	return (str);
}
