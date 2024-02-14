###########################################################################
#### SOURCES

SRC_FOLDER	= srcs/
SRC_FOLDER_BONUS = srcs/bonus/
BUILT_IN_DIR = built_ins/

BUILT_IN_FILES =	$(addprefix $(BUILT_IN_DIR), exit.c echo.c env.c built_in_utils.c unset.c export.c\
									pwd.c cd.c cd_utils.c cd_update_env_var.c)\

SRC_FILES	= main.c clean_exit.c init_struct.c signal.c parse_envp.c\
						update_shell_lvl.c $(BUILT_IN_FILES)\

AST_DIR = ast/
AST_FILES = $(addprefix $(AST_DIR), ast_init.c ast_new_node.c token_stream_copy.c \
						find_logical_opertor.c find_logical_operator2.c setup_recursive_calls.c\
						token_stream_node_management.c clear_stream_and_exit.c)
SRC_FILES	= main.c clean_exit.c init_struct.c signal.c tokenizer.c ast_tester.c\
						$(AST_FILES)

SRC_FILES_BONUS = 
BUILD = build/


OBJ_FILES	= $(addprefix $(BUILD),$(SRC_FILES:%.c=%.o))
OBJ_FILES_BONUS = $(addprefix $(SRC_FOLDER_BONUS), $(SRC_FILES_BONUS:%.c=%.o))

###########################################################################
#### ARGUMENTS

NAME		= minishell
<<<<<<< HEAD
CC			= cc
=======
CC			= gcc
>>>>>>> 8ec3da36f82fac68069ee142251b99f128c116cb
CFLAGS		= -Wall -Werror -Wextra -g3
LINKER = -lreadline

LIBFT_PATH	= libft/
LIBFT		= $(LIBFT_PATH)libft.a
INCLUDE	= minishell.h libft.h
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

$(NAME): $(OBJ_FILES)
	@make -C $(LIBFT_PATH) --no-print-directory -s
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(LINKER) -o $(NAME)
	@echo "$(MAGENTA)Les fichiers modifiés sont: $?$(RESET)"
	@echo "$(GREEN)Compilation réussie !$(RESET)"

build/%.o: srcs/%.c
	@mkdir -p ${BUILD}
	@mkdir -p ${BUILD}/${AST_DIR}
	@mkdir -p ${BUILD}/${BUILT_IN_DIR}
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
