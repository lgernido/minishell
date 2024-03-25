/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures_define_and_includes.h              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:05:02 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/25 15:32:16 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_DEFINE_AND_INCLUDES_H

# define DATA_STRUCTURES_DEFINE_AND_INCLUDES_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
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

# define NRM "\x1B[0m"
# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"

// For ft_pwd
# define PWD_BUFFER 128
# define BUFFER_LIMIT 4096

// Path to discards
# define STDIN_NODE 0
# define STD_IN_DEV "/dev/stdin"
# define STD_IN_PROC "/proc/self/fd/0"
# define STDOUT_NODE 1
# define STD_OUT_DEV "/dev/stdout"
# define STD_OUT_PROC "/proc/self/fd/1"

// For heredoc
# define BUFFER_MINISHELL 1024

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
	T_DOUBLE_QUOTED = 34,
	T_SINGLE_QUOTES = 39,
}								t_subtypes;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}								t_bool;

typedef struct s_sub_token
{
	t_subtypes					type;
	char						*value;
}								t_sub_token;

typedef struct s_sub_token_vector
{
	t_sub_token					**sub_token_list;
	size_t						vector_size;
	size_t						iterator;
}								t_sub_token_vector;

typedef struct s_token_stream_node
{
	char						*value;
	t_token_type				type;
	struct s_token_stream_node	*next;
	struct s_token_stream_node	*prev;
}								t_token_stream_node;

typedef struct s_command_node
{
	int							fd_infile;
	char						*here_doc;
	t_bool						is_here_doc;
	int							fd_outfile;
	int							pipe[2];
	char						**cmd;
	int							saved_infile;
	int							saved_outfile;
	t_token_stream_node			*redirections;
	struct s_command_node		*next;
	struct s_command_node		*prev;
}								t_command_node;

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

typedef struct s_wildcard_info
{
	char						**wildcard_tab;
	char						*entry_to_parse;
	t_bool						last_char_is_a_wildcard;
	t_bool						first_char_is_a_wildcard;
	DIR							*dir_ptr;
	t_token_stream_node			*token_stream;
}								t_wildcard_info;

typedef struct s_core
{
	t_ast_node					*ast;
	t_token_stream_node			*token_list;
	t_sub_token_vector			*sub_token_vector;
	char						**env;
	int							env_size;
	unsigned char				error_code;
}								t_core;

typedef struct stat				t_stat;
typedef int						(*t_built_ins)(char **av, t_core *core);
extern int						g_signal;

#endif
