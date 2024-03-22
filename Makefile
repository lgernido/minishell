###########################################################################
#### SOURCES

SRC_FOLDER	= srcs/
SRC_FOLDER_BONUS = srcs/bonus/

CLEAN_DIR = clean_and_error/
CLEAN_FILES = $(addprefix $(CLEAN_DIR), clean_command.c clean_main.c\
							clean_sub_vector.c clean_token_stream.c)

BUILT_IN_DIR = built_ins/
BUILT_IN_FILES =	$(addprefix $(BUILT_IN_DIR), exit.c echo.c env.c built_in_utils.c unset.c export.c\
									pwd.c cd.c cd_utils.c cd_update_env_var.c ft_get_env.c get_address.c\
									print_export.c)

AST_DIR = ast/
AST_FILES = $(addprefix $(AST_DIR), ast_init.c ast_new_node.c token_stream_copy.c\
						setup_recursive_calls.c token_stream_node_management.c\
						clear_stream_and_exit.c bridge_between_node.c ast_handling_utils.c\
						ft_pop_node.c)

SEARCH_DIR = search_in_token_stream/
SEARCH_FILES = $(addprefix $(SEARCH_DIR), find_logical_operator.c\
									 find_logical_operator2.c searching_functions1.c\
									 searching_functions2.c searching_functions3.c\
									 discard_parenthesis_utils.c)
PARSING_DIR = parsing/
PARSING_FILES = $(addprefix $(PARSING_DIR), parser.c parser_utils.c split_tokens.c \
								tokenizer.c tokenizer_utils.c)

EXPAND_DIR = expand/
EXPAND_FILES = $(addprefix $(EXPAND_DIR), expand_env_var.c expand_utils.c\
							 parse_token_word.c parsing_word_utils.c remove_quote.c\
							 sub_token_vector2.c sub_token_vector.c wildcards.c\
							 wildcard_init_functions.c wildcard_insert_substream.c\
							 wildcards_booleans.c wildcards_error_messages.c\
							 wildcards_matching_functions.c wildcards_utils.c)


PRE_EXEC_DIR = pre_exec_set_up/
PRE_EXEC_FILES = $(addprefix $(PRE_EXEC_DIR),command_list_base_funct.c\
								 expand_vars_and_wildcards_init.c fill_split_streams.c\
								 operator_stream.c shrink_list.c split_by_pipes.c\
								 turn_split_stream_in_command_list.c)

EXEC_DIR = exec/
EXEC_FILES = $(addprefix $(EXEC_DIR), child_routine.c discard_standard_entries.c\
						 exec_built_ins.c exec_error_message.c exec_init.c find_command_to_exec.c\
						 next_node.c parent_stuff.c pre_exec_setup.c redirection_handling_utils.c\
						 redirection_verfication.c resolve_operator.c syscalls_with_internal_error_throwing.c\
						 open_files.c)

SRC_FILES	= main.c init_struct.c signal.c parse_envp.c update_shell_lvl.c ast_tester.c\
						$(AST_FILES) $(BUILT_IN_FILES) $(SEARCH_FILES) $(PRE_EXEC_FILES) $(EXEC_FILES) driver.c\
						exec_driver.c $(EXPAND_FILES) $(CLEAN_FILES)



SRC_FILES_BONUS = 
BUILD = build/


OBJ_FILES	= $(addprefix $(BUILD),$(SRC_FILES:%.c=%.o))
OBJ_FILES_BONUS = $(addprefix $(SRC_FOLDER_BONUS), $(SRC_FILES_BONUS:%.c=%.o))

###########################################################################
#### ARGUMENTS

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3
LINKER = -lreadline

LIBFT_PATH	= libft/
LIBFT		= $(LIBFT_PATH)libft.a
INCLUDE	= minishell.h libft.h AST.h built_ins.h exec.h
INCLUDE_BONUS = 
INCLUDE_PATH = includes/

RED		=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
MAGENTA	=	\033[0;35m
CYAN	=	\033[0;36m
WHITE	=	\033[0;37m
RESET	=	\033[0m

###########################################################################
#### RULES

$(NAME): $(OBJ_FILES) $(INCLUDES)
	@make -C $(LIBFT_PATH) --no-print-directory -s
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(LINKER) -o $(NAME)
	@echo "$(MAGENTA)Les fichiers modifiés sont: $?$(RESET)"
	@echo "$(GREEN)Compilation réussie !$(RESET)"

build/%.o: srcs/%.c
	@mkdir -p ${BUILD}
	@mkdir -p ${BUILD}/${AST_DIR}
	@mkdir -p ${BUILD}/${CLEAN_DIR}
	@mkdir -p ${BUILD}/${BUILT_IN_DIR}
	@mkdir -p $(BUILD)/$(PARSING_DIR)
	@mkdir -p $(BUILD)/$(SEARCH_DIR)
	@mkdir -p $(BUILD)/$(PRE_EXEC_DIR)
	@mkdir -p $(BUILD)/$(EXEC_DIR)
	@mkdir -p $(BUILD)/$(EXPAND_DIR)
	@echo "$(YELLOW)Compilation de $*$(RESET)"
	@$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -I$(LIBFT_PATH) -I/usr/include -c $< -o $@

all : $(NAME)

clean :
	@rm -rf ${BUILD}
	@#@rm -f *.txt
	@rm -f *.o ${OBJ_FILES_BONUS}
	@make clean -C $(LIBFT_PATH) --no-print-directory -s
	@echo "$(CYAN) Nettoyage des fichiers intermédiaires $(RESET)"

fclean : clean
	@rm -f ${NAME}
	@make fclean -C $(LIBFT_PATH) --no-print-directory -s
	@echo "$(GREEN) Nettoyage terminé $(RESET)"

bonus : $(OBJ_FILES_BONUS)
	@make -C $(LIBFT_PATH) --no-print-directory -s
	@$(CC) $(CFLAGS) $(OBJ_FILES_BONUS) $(LIBFT) -o $(NAME)
	@echo "$(MAGENTA)Les fichiers modifiés sont: $?$(RESET)"
	@echo "$(GREEN)Compilation réussie !$(RESET)"

 
re : fclean all

.PHONY : all clean fclean re
