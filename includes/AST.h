/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:13:51 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/11 15:13:51 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H

# define AST_H

# include "minishell.h"

# define AND 0
# define OR 1
# define ANY 2

# define SUCESS_NODE 0
# define FAILURE_NODE 1

// ========================================================================= //

// AST usage fonctions in ast_new_node.c

// Create a new node. Return NULL in falure
t_ast_node			*ast_new_node(void); // ast_new_node.c

// Create a new nde and append it on the specified branch.
// No error on memory fail so errno need to be checked
void				ast_add_back(t_ast_node **ast, int mode); // ast_new_node.c

void				climb_tree_to_origin(t_ast_node **node); // ast_new_node.c

// ========================================================================= //

// Will copy every node of the list from given starting point to limit
// Limit can be set to NULL to copy the new list.
// Memory address are not shared, truly copy everything

void				ft_lst_cpy(t_core	*core, t_token_stream_node *src,
						t_token_stream_node **dest, t_token_stream_node *limit);
// in token_stream_copy.c

// ========================================================================= //

// token_strea_node_management.c

// Return NULL on error
t_token_stream_node	*ft_token_stream_new(t_token_type type, void *value);

// return NULL on error
void				ft_token_stream_add_back(t_token_stream_node **token_stream,
						t_token_stream_node *new_node);

void				ft_pop_node(t_token_stream_node **node_to_pop);

void				climb_stream_to_origin(t_token_stream_node **token_stream);

// ========================================================================= //

// In find_logical_operator.c

// Will clear the parenthesis pair, according to the address of the node send
void				discard_parenthesis(t_token_stream_node **token_stream);

// will return a pointer to the first operator. Mode : AND, OR, ANY
t_token_stream_node	*find_logical_operator(t_token_stream_node *token_stream,
						int mode);

// ========================================================================= //

// In find_logical_operator_2.c

// return true if mode match
t_bool				match_mode_condition(const int mode,
						const int searched_mode);

// return true if type match
t_bool				is_the_searched_token(const t_token_stream_node *token,
						const t_token_type searched_type);
// Used to jump around parenthesis so the operator inside isn't take in account
void				jump_above_parenthesis_if_needed(
						t_token_stream_node **token_stream);

// ========================================================================= //

// clear_stream_and_exit.c

// Will clear the stream who is not referenced by core, then cll clean exit
void				clear_stream_and_exit(t_core *core,
						t_token_stream_node *stream, int code);

// ========================================================================= //

// setup_recursive_call.c

// entry point for recursive call. Will copy the relevant part
// of the token stream in the node.
void				setup_current_node(t_token_stream_node *token_stream,
						t_core *core);

// Will dispatch the token stream between next nodes if needed
void				setup_recursive_calls(
						t_token_stream_node *stream_after_last_used_node,
						t_core *core);

#endif // !AST_H
