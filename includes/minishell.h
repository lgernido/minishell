/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:05:22 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/07 14:59:55 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdatomic.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

// easy pipe navigation
# define READ_ENTRY 0
# define WRITE_ENTRY 1

// Error Code

typedef enum e_error
{
	BAD_INFILE_PERM = 0,
	BAD_OUTFILE_PERM = 1,
	FORK_ERROR = 2,
	PIPE_ERROR = 3,
	DUP_ERROR = 4,
	MALLOC = 5,
	INFILE_IS_DIR = 6,
	OUTFILE_IS_DIR = 7,
	NOT_ENOUGH_ARGUMENT = 8,
	EXECVE_ERROR = 127
}					t_error;

typedef enum e_token_type
{
	AND,
	OR,
	SEMICOLON,
	SIMPLE_REDIR_LEFT,
	SIMPLE_REDIR_RIGHT,
	DOUBLE_REDIR_LEFT,
	DOUBLE_REDIR_RIGHT,
	PIPELINE,
	OPTION,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	BACKSLASH,
	LITERAL,
	VARIABLE,
	ESPACE,
}					t_token_type;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}					t_bool;

typedef struct s_command_node
{
	int fd_infile;               // exec
	char *infile;                // parsing -- NULL if pipe
	int fd_outfile;              // exec
	char *outfile;               // parsing -- NULL if pipe
	int pipe[2];                 // exec
	t_bool here_doc;             // parsing -- pas sur que y en a besoin
	char **cmd;                  // parsing
	struct s_command_node *next; // parsing -- NULL if first node
	struct s_command_node *prev; // parsing -- NULL if last node
}					t_command_node;

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
	t_token_stream_node	*token_stream;
	struct s_ast_node	*parent;
	struct s_ast_node	*on_success;
	struct s_ast_node	*on_failure;
}								t_ast_node;

typedef struct s_core
{
	t_ast_node	*ast;
	char		**envp;
	int			error_code;
}					t_core;

typedef struct s_token
{
	void			*value;
	t_token_type	type;
}					t_token;

extern atomic_int	g_signal;

// ========================================================================= //

// tokenizer.c //

// basic token management //
t_token				*ft_create_token(void *token_value,
						t_token_type token_type);
void				ft_clear_token(void *content);
t_token_type		ft_find_type(t_token *token);
t_token_type		ft_define_type(char charset);

// tokenize commands // 
void				ft_tokenizer(char *str);
void				ft_find_full_token(t_list **start, t_token_type type);
t_token				*ft_merge_token(t_token *token_1, t_token *token_2,
						t_token_type type);

// fix_syntax.c //

// fix operator tokens //
void				ft_fix_syntax(t_token token);
void				ft_fix_other_operators(t_token *token);
void				ft_fix_redirection(t_token *token);
void				ft_browse_list(t_list **start);

// utils //
t_bool				ft_is_operator(t_token_type type);
void				ft_error_found(char *msg1, char *arg, char *msg2);

// ========================================================================= //

// init_struct_and_parse_av.c //

// init core struct
void				init_core(t_core *core);

// init a new node
t_command_node		*init_node(t_command_node *node);

// Add a new node at the back of the given list
void				node_add_back(t_command_node **list, t_command_node *node);

// ========================================================================= //

// clean fonctions in clean_exit.c

// clean the core struct
void				ft_clean_exit(t_core *core, int code);

// clean the whole LL by calling ft_clean_node then exit
void				ft_command_clear(t_command_node **list);

// clean the given node
void				ft_clean_node(t_command_node *node);

// Clean the given token stream
void				ft_token_stream_clear(t_token_stream_node **token_stream);

// Clean the given node, for the token stream
void				ft_free_node(t_token_stream_node *node);

// ========================================================================= //

// Signal handler in signal.c \\

// init signal handling
void				init_sig(void);

// is call if global is updated
void				react_sig(t_core *core);

// ========================================================================= //

// utils for bult_in in built_in_utils.c

int					get_number_of_args(char **av);

// ========================================================================= //

// built-ins
int					echo(char **av);
void				ast_init(t_token_stream_node *token_stream, t_core *core);
void				split_str(t_core *core, char *str);

#endif
