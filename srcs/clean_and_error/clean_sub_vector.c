/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_sub_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:05:05 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 19:05:06 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "clean_and_error.h"

void	ft_clean_sub_token(t_sub_token **token)
{
	free_if_needed(&(*token)->value);
	free(*token);
	token = NULL;
	return ;
}

void	ft_clean_sub_token_list(t_sub_token **token_list, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (token_list[i] != NULL)
		{
			ft_clean_sub_token(&token_list[i]);
		}
		++i;
	}
	free(token_list);
}

void	ft_clean_sub_vector(t_sub_token_vector **vector)
{
	ft_clean_sub_token_list((*vector)->sub_token_list, (*vector)->vector_size);
	(*vector)->sub_token_list = NULL;
	free(*vector);
	*vector = NULL;
}
