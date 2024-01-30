FILES = ft_atoi.c	ft_isalpha.c	ft_itoa.c	ft_memmove.c	ft_putnbr_fd.c\
ft_strdup.c	ft_strlcpy.c	ft_strnstr.c	ft_tolower.c	ft_bzero.c\
ft_isascii.c	ft_memchr.c	ft_memset.c	ft_putstr_fd.c	ft_striteri.c\
ft_strlen.c	ft_strrchr.c	ft_toupper.c	ft_calloc.c	ft_isdigit.c\
ft_memcmp.c	ft_putchar_fd.c	ft_split.c	ft_strjoin.c	ft_strmapi.c\
ft_strtrim.c	ft_isalnum.c	ft_isprint.c	ft_memcpy.c	ft_putendl_fd.c\
ft_strchr.c	ft_strlcat.c	ft_strncmp.c	ft_substr.c\
ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c\
char_handling_bonus.c char_padding_bonus.c def_padding_bonus.c\
driver_bonus.c fill_padding_bonus.c int_handling_bonus.c\
itoa_base_bonus.c itoa_ptr_bonus.c lchexa_handling_bonus.c\
malloc_secure_bonus.c ptr_handling_bonus.c str_handling_bonus.c\
uchexa_handling_bonus.c unsgnd_int_handling_bonus.c\
get_next_line_bonus.c get_next_line_utils_bonus.c\
ft_freetab.c ft_atod.c

OBJECTS = ${FILES:.c=.o}

CC = cc -Wall -Wextra -Werror -g3

INCLUDES = includes/

NAME = libft.a

all : ${NAME}	

${NAME} : ${OBJECTS}
	@ar rcs $@ $^

%.o:%.c
	@${CC} -I $(INCLUDES) -c $< -o $@

clean :
	@rm -f ${OBJECTS} ${BONUS_OBJ}

fclean : 		clean
	@rm -f ${NAME} ${BONUS_OBJ}

re : fclean all

.PHONY : all re fclean clean bonus
