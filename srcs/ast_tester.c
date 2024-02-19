/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tester.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:28:55 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/13 12:28:56 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "AST.h"
#include <stdio.h>
#include <stdlib.h>

// To use me , call split_str to clam the readline input)

void	ft_create_token_stream(t_token_stream_node **stream, char *str)
{
	t_token_stream_node	*new_node;

	if (!ft_strncmp(str, "<", 2))
		new_node = ft_token_stream_new(T_INPUT_FILE, str);
	else if (!ft_strncmp(str, "<<", 3))
		new_node = ft_token_stream_new(T_HEREDOC, str);
	else if (!ft_strncmp(str, ">", 2))
		new_node = ft_token_stream_new(T_OUTPUT_FILE, str);
	else if (!ft_strncmp(str, ">>", 3))
		new_node = ft_token_stream_new(T_APPEND, str);
	else if (!ft_strncmp(str, "|", 2))
		new_node = ft_token_stream_new(T_PIPE, str);
	else if (!ft_strncmp(str, "||", 3))
		new_node = ft_token_stream_new(T_OR, str);
	else if (!ft_strncmp(str, "&&", 3))
		new_node = ft_token_stream_new(T_AND, str);
	else if (!ft_strncmp(str, "(", 2))
		new_node = ft_token_stream_new(T_PAR_OPEN, str);
	else if (!ft_strncmp(str, ")", 2))
		new_node = ft_token_stream_new(T_PAR_CLOSE, str);
	else
		new_node = ft_token_stream_new(T_WORD, str);
	ft_token_stream_add_back(stream, new_node);
}

void	print_token_stream(t_token_stream_node *stream)
{
	if (stream == NULL)
		return ;
	while (stream != NULL)
	{
		if (stream->value != NULL)
		{
			printf("%s, at adress %p ", (char *)stream->value, &stream->value);
			fflush(stdout);
		}
		stream = stream->next;
	}
}

void	print_splited_stream(t_token_stream_node **split_streams)
{
	int	i = 0;
	while (split_streams[i] != NULL)
	{
		printf("\nNew token stream :\n");
		print_token_stream(split_streams[i]);
		fflush(stdout);
		i++;
	}
	printf("\n");
}

void	print_tree(t_ast_node *ast)
{
	t_ast_node *tmp;

	if (ast == NULL)
		return ;
	climb_stream_to_origin(&ast->token_stream);
	printf("\nmy adress: %p", ast);
	printf("\nToken Stream for the node : ");
	print_token_stream(ast->token_stream);
	printf("\nAdress of sucess node : %p", ast->on_success);
	printf("\nAdress of failure node : %p\n\n\n\n", ast->on_failure);
	tmp = ast->on_success;
	print_tree(tmp);
	tmp = ast->on_failure;
	print_tree(tmp);
}

void	tokenize_str(t_core *core, char **str)
{
	t_token_stream_node	*stream;
	int	i = 0;

	stream = NULL;
	while (str[i] != NULL)
	{
		ft_create_token_stream(&stream, str[i]);
		free(str[i]);
		++i;
	}
	free(str);
	// print_token_stream(stream);
	// printf("Here ?\n");
	// fflush(stdout);
	ast_init(stream, core);
	printf("Return Here\n");
	fflush(stdout);
	climb_tree_to_origin(&core->ast);
	print_tree(core->ast);
	split_token_stream_by_pipes(core->ast);
	// print_splited_stream(core->ast->split_streams);
	shrink_stream(core->ast->split_streams);
	print_splited_stream(core->ast->split_streams);
	// ft_token_stream_clear(&stream);
	// ft_ast_clear(&core->ast);
}

void	split_str(t_core *core, char *str)
{
	char **splitted;

	splitted = ft_split(str, ' ');
	if (splitted == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	free(str);
	tokenize_str(core, splitted);
}
