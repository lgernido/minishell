/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:05:22 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/07 08:52:31 by lgernido         ###   ########.fr       */
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

typedef struct s_core
{
	t_command_node	*command_list;
	char			**envp;
	int				error_code;
}					t_core;

typedef struct s_token
{
	void			*value;
	t_token_type	type;
}					t_token;

extern atomic_int	g_signal;

// ========================================================================= //

// init_struct_and_parse_av.c //
void				ft_tokenizer(char *str);
void				ft_find_full_token(t_list **start, t_token_type type);
t_token				*ft_create_token(void *token_value,
						t_token_type token_type);
void				ft_clear_token(void *content);

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

#endif
