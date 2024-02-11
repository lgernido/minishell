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

typedef enum e_ast_token
{
	PIPE,
	LOGICAL_AND,
	LOGICAL_OR,
	WORD,
	TO_EXPAND_STR,
	NO_EXPAND_STR,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	INFILE_OPERATOR,
	HERE_DOC_OPERATOR,
	OUTPUT_OPERATOR,
	APPEND_OPERATOR,
}							t_ast_token;

typedef struct s_token_stream_node
{
	t_ast_token					type;
	void						*value;
	struct s_token_stream_node	*prev;
	struct s_token_stream_node	*next;
}								t_token_stream_node;

typedef struct s_ast_node
{
	t_command_node		*command_list;
	t_core				*core;
	struct s_ast_node	*on_success;
	struct s_ast_node	*on_failure;
}								t_ast_node;

#endif // !AST_H
