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
		new_node = ft_token_stream_new(INFILE_OPERATOR, str);
	else if (!ft_strncmp(str, "<<", 3))
		new_node = ft_token_stream_new(HERE_DOC_OPERATOR, str);
	else if (!ft_strncmp(str, ">", 2))
		new_node = ft_token_stream_new(OUTPUT_OPERATOR, str);
	else if (!ft_strncmp(str, ">>", 3))
		new_node = ft_token_stream_new(APPEND_OPERATOR, str);
	else if (!ft_strncmp(str, "|", 2))
		new_node = ft_token_stream_new(PIPE, str);
	else if (!ft_strncmp(str, "||", 3))
		new_node = ft_token_stream_new(LOGICAL_OR, str);
	else if (!ft_strncmp(str, "&&", 3))
		new_node = ft_token_stream_new(LOGICAL_AND, str);
	else if (!ft_strncmp(str, "(", 2))
		new_node = ft_token_stream_new(OPEN_PARENTHESIS, str);
	else if (!ft_strncmp(str, ")", 2))
		new_node = ft_token_stream_new(CLOSE_PARENTHESIS, str);
	else
		new_node = ft_token_stream_new(WORD, str);
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
			printf("%s ", (char *)stream->value);
			fflush(stdout);
		}
		stream = stream->next;
	}
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
	// ft_token_stream_clear(&stream);
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
