###########################################################################
#### SOURCES

SRC_FOLDER	= srcs/
SRC_FOLDER_BONUS = srcs/bonus/

SRC_FILES	= main.c clean_exit.c init_struct.c signal.c parse_envp.c\
						exit.c echo.c env.c built_in_utils.c unset.c
SRC_FILES_BONUS = 
BUILD = build/


OBJ_FILES	= $(addprefix $(BUILD),$(SRC_FILES:%.c=%.o))
OBJ_FILES_BONUS = $(addprefix $(SRC_FOLDER_BONUS), $(SRC_FILES_BONUS:%.c=%.o))

###########################################################################
#### ARGUMENTS

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -O3 -g3
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
	@$(CC) $(CFLAGS) ${LINKER} $(OBJ_FILES) $(LIBFT) -o $(NAME)
	@echo "$(MAGENTA)Les fichiers modifiés sont: $?$(RESET)"
	@echo "$(GREEN)Compilation réussie !$(RESET)"

build/%.o: srcs/%.c
	@mkdir -p ${BUILD}
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
