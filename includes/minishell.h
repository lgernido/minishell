/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:05:22 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/22 12:38:40 by lgernido         ###   ########.fr       */
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
# include <dirent.h>
# include <stdatomic.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

// easy pipe navigation
# define READ_ENTRY 0
# define WRITE_ENTRY 1

<<<<<<< HEAD
# define NRM "\x1B[0m"
# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"
=======
# define NRM  "\x1B[0m"
# define RED  "\x1B[31m"
# define GRN  "\x1B[32m"
# define YEL  "\x1B[33m"
# define BLU  "\x1B[34m"
# define MAG  "\x1B[35m"
# define CYN  "\x1B[36m"
# define WHT  "\x1B[37m"

>>>>>>> resolve_operator
// For ft_pwd
# define PWD_BUFFER 128
# define BUFFER_LIMIT 4096

// Path to discards
<<<<<<< HEAD

=======
# define STDIN_NODE 0
>>>>>>> resolve_operator
# define STD_IN_DEV "/dev/stdin"
# define STD_IN_PROC "/proc/self/fd/0"
# define STDOUT_NODE 1
# define STD_OUT_DEV "/dev/stdout"
# define STD_OUT_PROC "/proc/self/fd/1"

typedef enum e_error
{
	MALLOC = 1,
	EXECVE_ERROR = 127
}								t_error;

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
	T_SIMPLE_QUOTES,
	T_DOUBLE_QUOTES,
	T_LIM,
}								t_token_type;

typedef enum e_subtypes
{
	T_INIT = -1,
	T_REGULAR = 0,
	T_DOUBLE_QUOTES = 34,
	T_SINGLE_QUOTES = 39,
}						t_subtypes;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}								t_bool;

typedef struct s_sub_token
{
	t_subtypes	type;
	char		*value;
}								t_sub_token;

typedef struct s_sub_token_vector
{
	t_sub_token	**sub_token_list;
	size_t		vector_size;
	size_t		iterator;
}							t_sub_token_vector;

typedef struct s_token_stream_node
{
	t_token_type				type;
	char						*value;
	struct s_token_stream_node	*prev;
	struct s_token_stream_node	*next;
}								t_token_stream_node;

typedef struct s_command_node
{
<<<<<<< HEAD
	int							fd_infile;
	char						*here_doc;
	t_bool						is_here_doc;
	int							fd_outfile;
	int							pipe[2];
	char						**cmd;
	struct s_command_node		*next;
	struct s_command_node		*prev;
}								t_command_node;
=======
	int						fd_infile;	
	char					*here_doc;
	t_bool					is_here_doc;
	int						fd_outfile;
	int						pipe[2];
	char					**cmd;
	int						saved_infile;
	int						saved_outfile;
	t_token_stream_node		*redirections;
	struct s_command_node	*next;
	struct s_command_node	*prev;
}					t_command_node;
>>>>>>> resolve_operator

typedef struct s_ast_node
{
	t_token_stream_node			*token_stream;
	t_token_stream_node			**split_streams;
	t_command_node				*command_list;
	size_t						number_of_split_streams;
	struct s_ast_node			*parent;
	struct s_ast_node			*on_success;
	struct s_ast_node			*on_failure;
}								t_ast_node;

<<<<<<< HEAD
=======
typedef struct s_wildcard_info
{
	char				**wildcard_tab;
	char				*entry_to_parse;
	t_bool				last_char_is_a_wildcard;
	t_bool				first_char_is_a_wildcard;
	DIR					*dir_ptr;
	t_token_stream_node	*token_stream;
}							t_wildcard_info;

typedef struct s_core
{
	t_ast_node					*ast;
	struct s_token				*token_list;
	t_sub_token_vector			*sub_token_vector;
	char						**env;
	int							env_size;
	unsigned char				error_code;
}								t_core;

>>>>>>> resolve_operator
typedef struct s_token
{
	char						*value;
	int							type;
	struct s_token				*next;
	struct s_token				*prev;
}								t_token;
typedef struct s_core
{
	t_ast_node					*ast;
	t_token						*token_list;
	char						**env;
	int							env_size;
	int							error_code;
}								t_core;

extern atomic_int				g_signal;
typedef struct stat				t_stat;
typedef int						(*t_built_ins)(char **av, t_core *core);

// ========================================================================= //
/*PARSING*/

// parser.c //
int								ft_and_alone(char *str);
int								ft_syntax_check(char *str);
int								ft_start_parse(t_core *minishell, char *str);

// parser_utils.c//
int								ft_samestr(char *s1, char *s2);
void							ft_strdel(char **str);
int								ft_find_char_str(char c, char *str);
t_bool							ft_is_separator(char c);
int								ft_quotes(char *str);

// parser_utils2.c//

int								ft_is_ascii(char *str);
int								ft_handle_backslash(char *str);
int								ft_handle_dollar(char *str);
int								ft_dprintf(int fd, const char *format, ...);

// tokenizer.c//
int								ft_check_error(t_token *token);
int								ft_define_type(t_token *tmp);
int								ft_fix_redirect_types(t_token token_to_fix);
char							*ft_tokenizer(t_core *minishell);

// split_tokens.c //
int								ft_tokenize_quotes(t_core *minishell, char *str,
									t_token **start, int i);
int								ft_tokenize_variable(t_core *minishell,
									char *str, t_token **start, int i);
int								ft_tokenize_regular(t_core *minishell,
									char *str, t_token **start, int i);
int								ft_tokenize_special(t_core *minishell,
									char *str, t_token **start, int i);
void							ft_split_tokens(t_core *minishell, char *str);

// tokenizer_utils.c //
<<<<<<< HEAD
=======
t_token							*ft_create_arg_token(t_core *minishell,
									char *word, int type);
t_token							*ft_create_token(t_core *minishell, int i,
									char *str);
void							ft_clear_token_list(
									t_token **begin, void (*del)(void *));
int								ft_token_list_size(t_token **begin);
>>>>>>> resolve_operator
void							ft_add_token_list(t_token **begin,
									t_token *new);
void							ft_clear_token_list(t_token **begin);
t_token							*ft_create_token(t_core *minishell, int i,
									char *str);
t_token							*ft_create_priority_token(t_core *minishell,
									const char *str);
t_token							*ft_create_arg_token(t_core *minishell,
									char *word, int type);

// tokenizer_utils2.c //
int								ft_tokenize_redirections(t_core *minishell,
									char *str, t_token **start, int i);
int								ft_tokenize_parenthesis(t_core *minishell,
									char *str, t_token **start, int i);
int								ft_handle_dquote(t_core *minishell,
									char *user_input, int *i, t_token **start);
int								ft_handle_squote(t_core *minishell,
									char *user_input, int *i, t_token **start);

// here_doc.c //
int								ft_del_here_doc(void);
void							ft_here_doc_loop(char *delimiter, int fd);
void							ft_create_here_doc(t_core *minishell,
									char *delimiter);
void							ft_here_doc(t_core *minishell);

// =========================================================================
//

// init_struct_and_parse_av.c //

// init core struct
void							init_core(t_core *core);

<<<<<<< HEAD
// init a new node --> This must move
void							init_node(t_command_node *node);
t_command_node					*create_command_list_node(void);
void							command_node_add_back(t_command_node **command_list,
									t_command_node *new_node);
void							get_last_command_node(t_command_node **command_list);
void							update_command_list(t_core *core);
=======
// ========================================================================= //
>>>>>>> resolve_operator

// clean_main.c.c
// clean the core struct
void							ft_clean_exit(t_core *core, int code);

// ========================================================================= //

// In driver.c, it is the functions where the programm comes back
// after executing each command

// Entry point for handling a command. Is constantly called
// after programm init until the program exit.
void							minishell_driver(t_core *core);

// Wil call readline to get an input and return it.
char							*fetch_input(int error_code);

// In turn_split_stream_in_command_node.c
// Will take the split_stream (which , at this point, only contain)
// a command and it's argument, and turn it into char ** attach to
// the command node.
int								build_command_node(
									t_token_stream_node **command_stream,
									t_command_node *command_node);

// Exit if errno is set to ENOMEM. Used when a function who allocate have
// the right to return NULL ( "ex : > out | echo la" After handling
// Redirection, first node stream will be NULL).
void							check_errno(t_core *core);

// Entry point for expand var and parsing wildcards.
int								expand_init(t_core *core,
									t_token_stream_node *token_stream);

// Set up the token stream to have the appropriate form for exec
// Basically : Split the token stream to have one command node per command
// Call shrink_stream so every redirection are now only one node.
// Separate the redirections forom the command and arfuments
// Turn command and argument into a char **
// Call exec driver
void							ast_driver(t_core *core);

// Will either call the exec path that fork if the command
// is a pipeline/not a built-in single command,
// or the internal function exec in case of a single built-in.
void							exec_driver(t_core *core);

// For debuging exec purpose only.  Don't norm me !
t_token_stream_node *split_str(t_core *core, char *str);

// ========================================================================= //

// in command_list_base_function.c
// Will create a new command node , add it back to the end
// of the command node stream, and update the pointer to point to it.
void							update_command_list(t_core *core);

// ========================================================================= //

// parse_envp.c

<<<<<<< HEAD
// clean fonctions in clean_exit.c

// clean the core struct
void							ft_clean_exit(t_core *core, int code);

// clean the whole LL by calling ft_clean_node then exit
void							ft_command_clear(t_command_node **list);

// clean the given node
void							ft_clean_node(t_command_node *node);

// Call ft_token_stream_clear if the token isn't NULL
void							ft_clear_token_stream_if_needed(t_token_stream_node **token_stream);

// Clean the given token stream
void							ft_token_stream_clear(t_token_stream_node **token_stream);
void							ft_split_stream_clean(t_ast_node *ast);

// Clean the given node, for the token stream
void							ft_free_node(t_token_stream_node **node);

void							free_if_needed(void **str);
=======
// Parse envp if it exist, or set-up an empty one
void							handle_envp(char **envp, t_core *core);
>>>>>>> resolve_operator

// ========================================================================= //

// Signal handler in signal.c //

// init signal handling
void							init_sig(void);

// is call if global is updated
void							react_sig(t_core *core);

//
void							setup_exec_sig(void);

// ========================================================================= //

// Used to retrieve a var from env. var should include '$'
// --> char *str = ft_getenv(core, "$PATH"). return str should be fried
// find it in built_ins_utils.c
char							*ft_getenv(t_core *core, char *var);

// ========================================================================= //

// update shell level at start in update_shell_level.c
void							update_shell_lvl(t_core *core);

// ========================================================================= //

// built-ins in the built-ins folder
int								ft_echo(char **av, t_core *core); // echo.c
int								ft_cd(char **av, t_core *core); // cd.c
int								ft_exit(char **av, t_core *core); // exit.c
int								ft_pwd(char **av, t_core *core);
int								ft_env(char **av, t_core *core); // env.c
int								ft_unset(char **av, t_core *core); // unset.c
int								ft_export(char **av, t_core *core); // export.c

// ========================================================================= //

// Entry point for ast setup
void							ast_init(t_token_stream_node *token_stream,
									t_core *core);
void							ft_ast_clear(t_ast_node **node);

<<<<<<< HEAD
char							*fetch_input(t_core *core, int error_code);

// Call this functions just after retrieving user input
// to test ast without parsing
t_token_stream_node				*split_str(t_core *core, char *str);
void							minishell_driver(t_core *core);
int								translate_input(t_token_stream_node **input_stream,
									t_command_node *command_node);
int								translate_output(t_token_stream_node **output_stream,
									t_command_node *command_node);
int								build_command_node(t_token_stream_node **command_stream,
									t_token_stream_node **input_stream,
									t_token_stream_node **output_stream,
									t_command_node *command_node);
void							check_errno(t_core *core);

#endif

/*
Exec pseudo code :
	- Resolve var and wildcards // discard multiple files input
	- split into sub list by pipes
	- resolve infiles
	- resolve outfiles
	- build command
	- setup pipes and dup
	- check access
	- exec
*/
=======
#endif
>>>>>>> resolve_operator
