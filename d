PWD=/home/vlevy/minihell
OLDPWD=/home/vlevy/minihell
_=/home/vlevy/minihell/./minishell
LIBFT_PATH	= libft/
LIBFT		= $(LIBFT_PATH)libft.a
INCLUDE_PATH = includes/
	@make -C $(LIBFT_PATH) --no-print-directory -s
	@$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -I$(LIBFT_PATH) -I/usr/include -c $< -o $@
	@make clean -C $(LIBFT_PATH) --no-print-directory -s
	@make fclean -C $(LIBFT_PATH) --no-print-directory -s
	@make -C $(LIBFT_PATH) --no-print-directory -s
