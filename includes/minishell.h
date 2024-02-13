/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:05:22 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/13 10:56:04 by lgernido         ###   ########.fr       */
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
}

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

typedef struct s_core
{
	t_command_node	*command_list;
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

// tokenizer.c //

// Tokenize the input line
char				*ft_tokenizer(t_core *core);

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
int	echo(char **av, t_core *core);    // echo.c
int	ft_cd(char **av, t_core *core);   // cd.c
int	ft_exit(char **av, t_core *core); // exit.c
int					ft_pwd(char **av, t_core *core);
int	ft_env(char **av, t_core *core);    // env.c
int	ft_unset(char **av, t_core *core);  // unset.c
int	ft_export(char **av, t_core *core); // export.c

#endif
