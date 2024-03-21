/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:57:33 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 18:57:35 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_AND_ERROR_H

# define CLEAN_AND_ERROR_H

# include "minishell.h"

// ========================================================================= //

// Clean fonctions in clean_main.c

void							clean_prev_command(t_core *core);

// Rucursively call itself on every node of the ast until 
// the whole ast is cleared.
void							ft_ast_clear(t_ast_node **node);

// Clear the given AST node
void							ft_ast_node_clear(t_ast_node **node);

// free the given pointer it it isn't NULL.
void							free_if_needed(char **str);

// ========================================================================= //

// In clean_sub_vector.c

// free the sub_token_list
void							ft_clean_sub_token_list(
									t_sub_token **token_list, size_t size);

// free the sub_token_vector
void							ft_clean_sub_vector(
									t_sub_token_vector **vector);
// ========================================================================= //

// In clean_token_stream.c.c

// Call ft_token_stream_clear if the token isn't NULL
void							ft_clear_token_stream_if_needed(
									t_token_stream_node **token_stream);

// Clean the given token stream
void							ft_token_stream_clear(
									t_token_stream_node **token_stream);

// Clean all the split streams in the given split stream
void							ft_split_stream_clean(t_ast_node *ast);

// Clean the given node, for the token stream
void							ft_free_node(t_token_stream_node **node);

// ========================================================================= //

// In clean_command.c

// Take a pointer to the targeted fd. Will close it if it isn't set to -1
// then set it back to -1 to avoid trying to close it one more time.
void							close_if_open(int *fd);

// climb the linked list to the first node.
void							climb_command_list_to_origin(
									t_command_node **list);

// clean the whole list of command nodes by calling ft_clean_node then exit
void							ft_command_clear(t_command_node **list);

// clean the given command node
void							ft_clean_node(t_command_node *node);

#endif
