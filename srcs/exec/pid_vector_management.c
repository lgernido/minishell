/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_vector_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:12:42 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/01 19:12:44 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include <sys/types.h>

void	init_pids(pid_t *pid_vector, size_t vector_size)
{
	size_t	i;

	i = 0;
	while (i < vector_size)
	{
		pid_vector[i] = -1;
		++i;
	}
	return ;
}

void	init_pid_vector(t_core	*core, t_pid_vector *pid_vector)
{
	pid_vector = malloc(sizeof(t_pid_vector));
	if (pid_vector != NULL)
	{
		pid_vector->pids = malloc(8 * sizeof(pid_t));
	}
	if (pid_vector == NULL || pid_vector->pids == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	pid_vector->vector_size = 8;
	pid_vector->iterator_position = 0;
	init_pids(pid_vector->pids, pid_vector->vector_size);
	return ;
}

void	pid_t_cpy(pid_t *dest, pid_t *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		++i;
	}
	return ;
}

void	attach_pid_vector(t_ast_node *current_node, t_pid_vector *pid_vector)
{
	current_node->pid_vector = pid_vector;
	return ;
}

void	realloc_pid_vector(t_core *core, t_pid_vector *pid_vector)
{
	pid_t	*new_pid_vector;

	new_pid_vector = malloc(pid_vector->vector_size * 2 * sizeof(pid_t));
	if (new_pid_vector == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	init_pids(new_pid_vector, 2 * pid_vector->vector_size);
	pid_t_cpy(new_pid_vector, pid_vector->pids, pid_vector->vector_size);
	pid_vector->vector_size *= 2;
	free(pid_vector->pids);
	pid_vector->pids = new_pid_vector;
}

void	update_iterator_position(t_core *core, t_pid_vector *pid_vector)
{
	pid_vector->iterator_position += 1;
	if (pid_vector->iterator_position >= pid_vector->vector_size)
	{
		realloc_pid_vector(core, pid_vector);
	}
	return ;
}
