/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:05:22 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/13 14:54:14 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft.h"
# include "printerr.h"
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

// For ft_pwd
# define PWD_BUFFER 128
# define BUFFER_LIMIT 4096
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

typedef enum e_token_types
{
	T_WORD,
	T_REDIRECT,
	T_PIPE,
	T_SEP,
	T_NEWLINE,
	T_AND,
	T_OR,
	T_PAR_OPEN,
	T_PAR_CLOSE,
	T_INPUT_FILE,
	T_OUTPUT_FILE,
	T_HEREDOC,
	T_APPEND,
	T_TO_EXPAND,
	T_NO_EXPAND,
}						t_token_type;

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

typedef struct s_token_stream_node
{
	t_token_type				type;
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
	t_ast_node		*ast;
	struct s_token	*token_list;
	char			**env;
	int				env_size;
	int				error_code;
}					t_core;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

extern atomic_int	g_signal;

// ========================================================================= //
/*PARSING*/

// parser.c //
void				ft_start_parse(t_core *minishell, char *str);

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
// parser_utils.c//
int					ft_quotes(char *s, int pos);
int					ft_escape(char *s, int pos);
int					ft_find_char_str(char c, char *str);
int					ft_samestr(char *s1, char *s2);

// tokenizer.c//
int					ft_check_error(t_token *token);
int					ft_define_type(t_token *tmp);
char				*ft_tokenizer(t_core *minishell);
void				ft_fix_redirect_types(t_token token_to_fix);
// split_tokens.c //
int					ft_split_utils(int i, char *str, char *sep, int sign);
int					ft_split_tokens2(t_core *minishell, char *str, int *i,
						t_token **start);
void				ft_split_tokens(t_core *minishell, char *str);

// fix operator tokens //
void				ft_fix_syntax(t_token token);
void				ft_fix_other_operators(t_token *token);
void				ft_fix_redirection(t_token *token);
void				ft_browse_list(t_list **start);

// utils //
t_bool				ft_is_operator(t_token_type type);
void				ft_error_found(char *msg1, char *arg, char *msg2);
// tokenizer_utils.c //
t_token				*ft_create_arg_token(char *word, int type);
t_token				*ft_create_token(t_core *minishell, int i, char *str);
void				ft_clear_token_list(t_token **begin, void (*del)(void *));
int					ft_token_list_size(t_token **begin);
void				ft_add_token_list(t_token **begin, t_token *new);

// ========================================================================= //

// init_struct_and_parse_av.c //

// init core struct
void				init_core(t_core *core);

// init a new node
t_command_node		*init_node(t_command_node *node);

// Add a new node at the back of the given list
void				node_add_back(t_command_node **list, t_command_node *node);

// ========================================================================= //

// parse_envp.c
void				parse_envp(char **envp, t_core *core);

// clean fonctions in clean_exit.c

// clean the core struct
void				ft_clean_exit(t_core *core, int code);

// clean the whole LL by calling ft_clean_node then exit
void				ft_command_clear(t_command_node **list);

// clean the given node
void				ft_clean_node(t_command_node *node);

// Call ft_token_stream_clear if the token isn't NULL
void				ft_clear_token_stream_if_needed(
						t_token_stream_node **token_stream);

// Clean the given token stream
void				ft_token_stream_clear(t_token_stream_node **token_stream);

// Clean the given node, for the token stream
void				ft_free_node(t_token_stream_node *node);

// ========================================================================= //

// Signal handler in signal.c //

// init signal handling
void				init_sig(void);

// is call if global is updated
void				react_sig(t_core *core);

// ========================================================================= //

// Used to retrieve a var from env. var should include '$'
// --> char *str = ft_getenv(core, "$PATH"). return str should be fried
// find it in built_ins_utils.c
char				*ft_getenv(t_core *core, char *var);

// ========================================================================= //

// update shell level at start in update_shell_level.c
void				update_shell_lvl(t_core *core);

// ========================================================================= //

// built-ins
int					echo(char **av, t_core *core); // echo.c
int					ft_cd(char **av, t_core *core); // cd.c
int					ft_exit(char **av, t_core *core); // exit.c
int					ft_pwd(char **av, t_core *core);
int					ft_env(char **av, t_core *core); // env.c
int					ft_unset(char **av, t_core *core); // unset.c
int					ft_export(char **av, t_core *core); // export.c

// Entry point for ast setup
void				ast_init(t_token_stream_node *token_stream, t_core *core);

// Call this functions just after retrieving user input
// to test ast without parsing
void				split_str(t_core *core, char *str);

#endif
