/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token_stream.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:09:42 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 19:09:43 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "clean_and_error.h"
#include "AST.h"

void	ft_free_node(t_token_stream_node **node)
{
	if (*node == NULL)
		return ;
	if ((*node)->value)
	{
		free((*node)->value);
	}
	free(*node);
	*node = NULL;
}

void	ft_clear_token_stream_if_needed(t_token_stream_node **token_stream)
{
	if (*token_stream != NULL)
	{
		ft_token_stream_clear(token_stream);
	}
}

void	ft_token_stream_clear(t_token_stream_node **token_stream)
{
	t_token_stream_node	*tmp;

	climb_stream_to_origin(token_stream);
	while (*token_stream != NULL)
	{
		tmp = (*token_stream)->next;
		ft_free_node(token_stream);
		*token_stream = tmp;
	}
	*token_stream = NULL;
}

void	ft_split_stream_clean(t_ast_node *ast)
{
	t_token_stream_node	**tmp;
	size_t				i;

	i = 0;
	tmp = ast->split_streams;
	while (i < ast->number_of_split_streams)
	{
		ft_token_stream_clear(&(tmp[i]));
		i++;
	}
	free(tmp);
	ast->split_streams = NULL;
}
