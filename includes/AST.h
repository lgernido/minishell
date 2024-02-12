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

// ========================================================================= //

// AST usage fonctions

t_ast_node	*ast_new_node(void); // ast_new.c

// Find logical op
t_bool		match_type_condition(const t_ast_token type,
				const t_ast_token searched_type);
t_bool		match_mode_condition(const int mode, const int searched_mode);
t_bool		is_the_searched_token(const t_token_stream_node *token,
				const t_ast_token searched_type);
void		jump_above_parenthesis(t_token_stream_node **token);

#endif // !AST_H
