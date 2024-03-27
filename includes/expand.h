/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:35:46 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/18 12:35:47 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H

# define EXPAND_H

# include "minishell.h"

// ========================================================================= //

// In parse_token_word.c

// Entry point for parsing a word into sub_tokens
void	parse_word_init(t_core *core, char *token_string);

// ========================================================================= //

// In parsing_word_utils.c

// Return TRUE if the quote should be read as a meta character.
t_bool	is_a_relevant_quote(int c, int flag);

// Update the state of the current_quote flag.
void	update_current_quote(int *current_quote, int quote);
// ========================================================================= //

// In sub_token_vector.c

// Will init a new vector of sub_tokens.
int		init_vector(t_core *core);

// Will create a new sub_token to the next available place, then
// update the iterator to the next available position.
int		create_new_sub_token(t_core *core, char *new_token_start,
			char *new_token_end, t_subtypes type);

// Will join all the vector in a new string,
// removing quotes and highlighting wildcards before
char	*join_vector_in_a_string(t_core *core);

// ========================================================================= //

// In sub_token_vector2.c

// Take a pointer to the beginning of the string and one to the end.
// Copy the string part in a new one.
char	*ft_strndup(char *start, char *end);

// Update the iterator position of one. If it reaches the end
// of the subvector array, reallocate it by twice his size,
int		update_iterator_position(t_core *core);

// ========================================================================= //

// In expand_env_var.c

// Expand all the variable in the current sub_token.
char	*expand_var_init(t_core *core, char *str);

// ========================================================================= //

// In expand_utils.c

// Return TRUE if the token type is double quotes or word
t_bool	sub_token_need_expand(t_sub_token *sub_token);

// Setup for safe expand
void	expand_sub_token(t_core *core, int i);

// Return the end of a var
char	*find_var_end(char *var_begin);

// Return True if the char marks the end of a var.
t_bool	is_valid_var_ender(char c);

// Return True if hidden files must me listed.
t_bool	is_an_entry_to_parse(t_wildcard_info *info);

// ========================================================================= //

// In remove_quotes.c

// If the sub token is single or double quote, remove the quotes.
// If it is a T_WORD token, highlights wildcards, turning them into (-42)
void	remove_quotes_and_highlight_wildcards(t_core *core);

// ========================================================================= //

// In wildcard.c

// Entry point for matching wildcards.
int		wildcards_init(t_core *core, t_token_stream_node **current_token);

// ========================================================================= //

// In wildcard_matching_functions.c

// Return TRUE if the char is equal to -42.
t_bool	is_a_wildcard(char c);

// Return TRUE if the last char of the string is equal to -42.
t_bool	is_last_char_a_wildcard(char *str);

// Return TRUE if one more matching call need to be done 
// with the end of the string.
t_bool	need_to_check_end_of_string(char *tmp_str,
			t_wildcard_info *wildcard_info);

// Return TRUE if the previous node exists and his a redirection operator.
t_bool	is_prev_node_is_a_redirection(t_token_stream_node *current_token);

// ========================================================================= //

// In wildcard_matching_functions.c

// match the word anywhere in the remaining part of the string.
t_bool	match_wildcard_entry(char **big, const char *little);

// match the word only if it is the very end of the string.
t_bool	check_end_of_string(char *big, char *little);

// match the word only if it is the very begining of the string.
t_bool	check_beginning_of_string(char	*big, char *little);

// ========================================================================= //

// In wildcards_utils.c

// If the entry match the wildcard pattern, will save it in the token_stream
// attach to wildcards_info. Exit the programm on ENOMEM.
void	save_dir_entry(t_core	*core, t_wildcard_info *wildcard_info);

// Free all the ressources of wildcard_info and close the dir. 
void	clean_wildcard_info(t_wildcard_info *wildcard_info);

// Call if no match is found. Will replace the wildcard char (-42)
// by regular * (42).
void	remove_highlighted_char(char *str, int to_remove);

// Return the size of the token_stream.
size_t	ft_token_stream_size(t_token_stream_node *token_stream);

// ========================================================================= //

// In wildcards_init_function.c

// Will fill the fields of the wildcard struct to NULL or 0,
// except for the booleans one that will be set to TRUE or FALSE
// according to the wildcard pattern
int		init_wildcards_info(t_wildcard_info *wildcards_info,
			char *wildcard_string, DIR	*dir_ptr);

// Open the directory. Exit program on error.
DIR		*open_dir(t_core *core);

// ========================================================================= //

// In wildcards_insert_substream.c

// Will take the substream of the dir entries that matches with the 
// wildcard pattern and insert it in the main stream.
// If there is more than one match
// And the prev token is a redirection, it will throw an error
// and return -1. Return 0 otherwise
int		insert_entries_in_stream(t_token_stream_node **current_token,
			t_token_stream_node **entries_stream,
			const t_bool is_prev_node_a_redir);

#endif
