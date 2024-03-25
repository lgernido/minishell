/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:05:22 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/25 16:07:00 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "data_structures_define_and_includes.h"
# include "libft.h"
# include "printerr.h"

// ========================================================================= //
/*PARSING*/

// parser.c //
int					ft_and_alone(char *str);
int					ft_syntax_check(char *str);
int					ft_start_parse(t_core *minishell, char *str);

// parser_utils.c//
int					ft_samestr(char *s1, char *s2);
void				ft_strdel(char **str);
int					ft_find_char_str(char c, char *str);
t_bool				ft_is_separator(char c);
int					count_parenthesis(char *str);

// parse_quotes.c//
int					ft_quotes(char *str);
int					ft_handle_quoted_token(t_core *minishell, char *str,
						t_token_stream_node**start, int i);

// tokenize_nested_quotes.c//

int					tokenize_nested_quotes(t_core *minishell, char *str,
						t_token_stream_node**start, size_t i);
void				update_flag(int *flag, char quote_to_check);

// parser_utils2.c//

int					ft_is_ascii(char *str);
int					ft_handle_backslash(char *str);
int					ft_handle_dollar(char *str);
int					ft_dprintf(int fd, const char *format, ...);

// tokenizer.c//
int					ft_check_error(t_token_stream_node*token);
int					ft_define_type(t_token_stream_node*tmp);
int					ft_fix_redirect_types(t_token_stream_node token_to_fix);
char				*ft_tokenizer(t_core *minishell);

// check_parenthesis.c //
int					check_open_parenthesis(t_token_stream_node*stream);
int					check_close_parenthesis(t_token_stream_node*stream);

// split_tokens.c //
int					ft_tokenize_quotes(t_core *minishell, char *str,
						t_token_stream_node**start, int i);
int					ft_tokenize_variable(t_core *minishell, char *str,
						t_token_stream_node**start, int i);
int					ft_tokenize_regular(t_core *minishell, char *str,
						t_token_stream_node**start, int i);
int					ft_tokenize_special(t_core *minishell, char *str,
						t_token_stream_node**start, int i);
void				ft_split_tokens(t_core *minishell, char *str);

// tokenizer_utils.c //
t_token_stream_node	*ft_create_arg_token(t_core *minishell, char *word,
						int type, char *str);
t_token_stream_node	*ft_create_token(t_core *minishell, int i, char *str);
int					ft_token_list_size(t_token_stream_node**begin);
void				ft_add_token_list(
						t_token_stream_node**begin, t_token_stream_node *new);
void				ft_clear_token_list(t_token_stream_node**begin);
t_token_stream_node	*ft_create_token(t_core *minishell, int i, char *str);
t_token_stream_node	*ft_create_priority_token(t_core *minishell,
						const char *token, char *str);

// tokenizer_utils2.c //
int					ft_tokenize_redirections(t_core *minishell, char *str,
						t_token_stream_node**start, int i);
int					ft_tokenize_parenthesis(t_core *minishell, char *str,
						t_token_stream_node**start, int i);
int					ft_handle_dquote(t_core *minishell, char *user_input,
						int *i, t_token_stream_node**start);
int					ft_handle_squote(t_core *minishell, char *user_input,
						int *i, t_token_stream_node**start);

// here_doc.c //
int					ft_del_here_doc(void);
int					ft_here_doc(t_core *minishell);

// =========================================================================
//

// init_struct_and_parse_av.c //

// init core struct
void				init_core(t_core *core);

// ========================================================================= //

// clean_main.c.c
// clean the core struct
void				ft_clean_exit(t_core *core, int code);

// ========================================================================= //

// In driver.c, it is the functions where the programm comes back
// after executing each command

// Entry point for handling a command. Is constantly called
// after programm init until the program exit.
void				minishell_driver(t_core *core);

// In turn_split_stream_in_command_node.c
// Will take the split_stream (which , at this point, only contain)
// a command and it's argument, and turn it into char ** attach to
// the command node.
int					build_command_node(t_token_stream_node **command_stream,
						t_command_node *command_node);

// Exit if errno is set to ENOMEM. Used when a function who allocate have
// the right to return NULL ( "ex : > out | echo la" After handling
// Redirection, first node stream will be NULL).
void				check_errno(t_core *core);

// Entry point for expand var and parsing wildcards.
int					expand_init(t_core *core,
						t_token_stream_node *token_stream);

// Set up the token stream to have the appropriate form for exec
// Basically : Split the token stream to have one command node per command
// Call shrink_stream so every redirection are now only one node.
// Separate the redirections forom the command and arfuments
// Turn command and argument into a char **
// Call exec driver
void				ast_driver(t_core *core);

// Will either call the exec path that fork if the command
// is a pipeline/not a built-in single command,
// or the internal function exec in case of a single built-in.
void				exec_driver(t_core *core);

// For debuging exec purpose only.  Don't norm me !
t_token_stream_node	*split_str(t_core *core, char *str);

// ========================================================================= //

// in command_list_base_function.c
// Will create a new command node , add it back to the end
// of the command node stream, and update the pointer to point to it.
void				update_command_list(t_core *core);

// ========================================================================= //

// parse_envp.c

// Parse envp if it exist, or set-up an empty one
void				handle_envp(char **envp, t_core *core);

// ========================================================================= //

// Signal handler in signal.c //

// init signal handling
void				init_sig(void);

// is call if global is updated
void				react_sig(t_core *core);

void				parsing_sig(void);
//
void				setup_exec_sig(void);

// ========================================================================= //

// Used to retrieve a var from env. var should include '$'
// --> char *str = ft_getenv(core, "$PATH"). return str should be fried
// find it in built_ins_utils.c
char				*ft_getenv(t_core *core, char *var);

// ========================================================================= //

// update shell level at start in update_shell_level.c
void				update_shell_lvl(t_core *core);

// ========================================================================= //

// built-ins in the built-ins folder
int					ft_echo(char **av, t_core *core); // echo.c
int					ft_cd(char **av, t_core *core); // cd.c
int					ft_exit(char **av, t_core *core); // exit.c
int					ft_pwd(char **av, t_core *core);
int					ft_env(char **av, t_core *core); // env.c
int					ft_unset(char **av, t_core *core); // unset.c
int					ft_export(char **av, t_core *core); // export.c

// ========================================================================= //

// Entry point for ast setup
void				ast_init(t_token_stream_node *token_stream, t_core *core);
void				ft_ast_clear(t_ast_node **node);

char				*fetch_input(int error_code);
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
#endif
