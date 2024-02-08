/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:05:22 by purmerinos        #+#    #+#             */
/*   Updated: 2024/01/29 17:05:22 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdatomic.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <time.h>
# include <errno.h>
# include <sys/wait.h>
# include "printerr.h"
# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

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
}							t_error;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}						t_bool;

typedef struct s_command_node
{
	int				fd_infile; // exec
	char			*infile; // parsing -- NULL if pipe
	int				fd_outfile; // exec
	char			*outfile; // parsing -- NULL if pipe
	int				pipe[2]; // exec
	t_bool		here_doc; // parsing -- pas sur que y en a besoin
	char			**cmd; // parsing
	struct s_command_node		*next; // parsing -- NULL if first node
	struct s_command_node		*prev; // parsing -- NULL if last node
}								t_command_node;

typedef struct s_core
{
	t_command_node	*command_list;
	char			**env;
	int				env_size;
	int				error_code;
}								t_core;

extern atomic_int	g_signal;

// ========================================================================= \\

// init_struct_and_parse_av.c \\

// init core struct
void			init_core(t_core *core);

// init a new node
t_command_node	*init_node(t_command_node *node);

// Add a new node at the back of the given list
void			node_add_back(t_command_node **list, t_command_node *node);

// ========================================================================= //

// parse_envp.c 
void			parse_envp(char **envp, t_core *core);

// clean fonctions in clean_exit.c

// clean the core struct
void			ft_clean_exit(t_core *core, int code);

// clean the whole LL by calling ft_clean_node then exit
void			ft_command_clear(t_command_node **list);

// clean the given node
void			ft_clean_node(t_command_node *node);

// ========================================================================= //

// Signal handler in signal.c \\

// init signal handling
void			init_sig(void);

// is call if global is updated
void			react_sig(t_core *core);

// ========================================================================= //

// utils for bult_in in built_in_utils.c
int				get_number_of_args(char **av);
// check if the var has been unset
t_bool			is_set(char *str);
// used to update var
char			**get_valid_addr(t_core *core, char *av);

// Used by export
t_bool			is_the_var(char *var, char *env);
void			print_export(char **env);

// Used to retrieve a var from env. var should include '$'
// --> char *str = ft_getenv(core, "$PATH"). return str should be fried
char			*ft_getenv(t_core *core, char *var);
// ========================================================================= //

// built-ins
int				echo(char **av, t_core *core); // echo.c
int				ft_cd(char **av, t_core *core); // cd.c
int				ft_exit(char **av, t_core *core); // exit.c
int				ft_pwd(char **av, t_core *core);
int				ft_env(char **av, t_core *core); // env.c
int				ft_unset(char **av, t_core *core); // unset.c
int				ft_export(char **av, t_core *core); //export.c

// ========================================================================= //
// cd_utils.c && cd_update_env_var.c
void			too_many_args(void *arg);
char			*assign_pwd(t_core *core);
void			update_env_var(t_core	*core, char *old_pwd);
void			home_not_set(void *arg);
void			error_while_shifting_directory(void *path);
int				go_specified_dir(void	*path);
int				throw_error_message(void *arg, void (*message)(void *));
char			*get_pwd_in_buffer(void);
char			*get_pwd(char *buffer, int len);
#endif
