/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:30:24 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/29 17:30:25 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H

# include "minishell.h"

void	close_if_open(int *fd);
void	safely_close_pipe_entry(t_command_node *node, int entry_to_close);
void	retrieve_path(t_core *core, t_command_node *current_command);
void	child_routine(t_core *core, t_command_node *current_command);
void	init_pid_vector(t_core	*core, t_pid_vector *pid_vector);
void	update_iterator_position(t_core *core, t_pid_vector *pid_vector);
void	attach_pid_vector(t_ast_node *current_node, t_pid_vector *pid_vector);

#endif
