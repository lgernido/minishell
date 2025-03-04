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

// Will copy every node of the list from given starting point to limit.
// Limit can be set to NULL to copy the whole list.
// Memory address are not shared, truly copy everything
// On mempry failure, will clear dest , set errno to ENOMEM, then return
void				ft_lst_cpy(t_token_stream_node *src,
						t_token_stream_node **dest, t_token_stream_node *limit);
// in token_stream_copy.c

// ========================================================================= //

// token_strea_node_management.c

// Return NULL on error
t_token_stream_node	*ft_token_stream_new(t_token_type type, void *value);

// return NULL on error
void				ft_token_stream_add_back(t_token_stream_node **token_stream,
						t_token_stream_node *new_node);

void				ft_del_node(t_token_stream_node **node_to_del);

void				ft_extract_node(t_token_stream_node **node_to_pop);

void				climb_stream_to_origin(t_token_stream_node **token_stream);

// ========================================================================= //

// In find_logical_operator.c

// Will clear the parenthesis pair, according to the address of the node send
void				discard_parenthesis(t_token_stream_node **token_stream);

// will return a pointer to the first operator. The second parameter should 
// be the functions that will identify the searched token type(s)
t_token_stream_node	*find_searched_token(t_token_stream_node *token_stream,
						t_bool (*searched_token)(t_token_stream_node *token));

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
						t_token_stream_node **stream, int code);

// Will call clear_stream_and_exit if errno is set to ENOMEM
void				check_for_error(t_core	*core,
						t_token_stream_node **first_token_stream,
						t_token_stream_node **second_token_stream);

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

// ========================================================================= //

// ast_handling_utils.c

// Dereference token stream and attach it to node,
// then set the pointer to null
void				attach_token_stream(t_ast_node **node,
						t_token_stream_node **to_attach);

// Attach the token stream of the ast node to an external pointer,
// and set it to NULL
void				detach_token_stream(t_ast_node **node,
						t_token_stream_node **to_attach);
// Reset AST to the parent node
void				reset_ast(t_ast_node **node);

// ========================================================================= //

// bridge_between_node.c

// Return the address of the success or failure node, depending
// of the mode it was called with.
t_ast_node			*return_relevant_node(t_ast_node *node, int mode);

// Create a new node, add it to the specifed branch of ast, 
// and attach the relevant token stream to it
void				setup_new_node(t_core *core,
						t_token_stream_node **on_success,
						t_token_stream_node **on_failure, int mode);

// ========================================================================= //

// find_logical_operator.c, searching_functions1-2-3.c 
// All this functions are meant to be passed as the parameter of other 
// functions to match one or more token type;

t_bool				find_logical_and(t_token_stream_node *token);
t_bool				find_logical_or(t_token_stream_node *token);
t_bool				find_logical_operator(t_token_stream_node *token);
t_bool				find_pipe(t_token_stream_node *token);
t_bool				find_infile_operator(t_token_stream_node *token);
t_bool				find_here_doc_operator(t_token_stream_node *token);
t_bool				find_outfile_operator(t_token_stream_node *token);
t_bool				find_append_operator(t_token_stream_node *token);
t_bool				find_input_operator(t_token_stream_node *token);
t_bool				find_output_operator(t_token_stream_node *token);
t_bool				find_redirection_operator(t_token_stream_node *token);

// ========================================================================= //

// In discard_parenthesis_utils.c 

// return 1 if the token is an open parenthsis
size_t				check_for_parenthesis(t_token_stream_node *node,
						t_token_type searched);

// Decrement the parenthesis counter by one if the tken type 
// is close parenthesis. Delete the node if the counter value is 0.
void				check_for_closing_parenthesis(
						t_token_stream_node **node,
						size_t *parenthesis_counter);
// Will be called whenever the first token of a new AST need is 
// an open parenthesis , meaning that the parenthesis pair
// should be discard.
void				free_first_parenthesis(t_token_stream_node **token_stream);

// In split_by_pipes.c
// Will count the number of pipe in an AST node and allocate the 
// number of stream pointers needed to split the pipeline by pipes
void				split_token_stream_by_pipes(t_ast_node *node);

// In fill_split_streams.c
// Will fill the allocated space with the token_stream relevant for each pipe
void				fill_stream(t_ast_node *node,
						const size_t index_in_split_streams);

// In resolve_opertor.c
// Will set the stream pointer to next if it isn't NULL.
void				update_stream_if_needed(t_token_stream_node **token_stream);

// In shrink_list.c
// Will go through the stream, and, everytime a redirection operator is found
// It will assign the value of the folllowing token to the value of the
// redirection operator, then pop the node following the operator.
void				shrink_stream(t_token_stream_node **stream);

// In operator_stream.c
// Will extract all the redirection token to put them in a new stream, so 
// there are now two stream : On with only the command and argument,
// and one with all the redirections. Redirection order is preserved.
t_token_stream_node	*build_operator_stream(t_token_stream_node **stream,
						t_bool (*searching_function)
						(t_token_stream_node *token));

void				safely_del_node(t_token_stream_node **node);

#endif // !AST_H
