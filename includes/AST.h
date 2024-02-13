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

// AST usage fonctions

t_ast_node			*ast_new_node(void); // ast_new.c

// Find logical op
t_token_stream_node	*ft_token_stream_new(t_ast_token type, void *value);
t_bool				match_type_condition(const t_ast_token type,
						const t_ast_token searched_type);
t_bool				match_mode_condition(const int mode,
						const int searched_mode);
t_bool				is_the_searched_token(const t_token_stream_node *token,
						const t_ast_token searched_type);
void				jump_above_parenthesis(t_token_stream_node **token);
void				ft_token_stream_add_back(t_token_stream_node **token_stream,
						t_token_stream_node *new_node);
void				ft_lst_cpy(t_core	*core, t_token_stream_node *src,
						t_token_stream_node **dest, t_token_stream_node *limit);
void				ft_free_node(t_token_stream_node *node);
void				ft_pop_node(t_token_stream_node **node_to_pop);
t_token_stream_node	*find_logical_operator(t_token_stream_node *token_stream,
						int mode);
void				climb_tree_to_origin(t_ast_node **node);
void				ft_token_stream_clear(t_token_stream_node **token_stream);
void				climb_stream_to_origin(t_token_stream_node **token_stream);
void				setup_ast(t_token_stream_node *token_stream, t_core *core);
void				setup_recursive_calls(t_token_stream_node *stream_after_last_used_node,
						t_core *core);
void				discard_parenthesis(t_token_stream_node **token_stream);
void				ast_add_back(t_ast_node **ast, int mode);
void				clear_stream_and_exit(t_core *core,
						t_token_stream_node *stream, int code);

#endif // !AST_H
