NAME = minishell

SRC =	main.c \
		set_up.c \
		ft_read_input.c \
		ft_parse_input.c \
		ft_parse_input2.c \
		ft_create_list.c \
		minishell_utils.c \
		error.c \
		error2.c \
		export.c \
		cd.c \
		env.c \
		ft_expand.c \
		ft_expand2.c \
		ft_free.c \
		pwd.c \
		ft_proceniser.c \
		ft_tokenizer.c \
		ft_print.c \
		unset.c \
		signals.c \
		exit.c \
		ft_launch_process.c \
		ft_create_children.c \
		ft_pipes_utils.c \
		ft_redirection_parse.c \
		ft_red_in_utils.c \
		ft_red_out_app_utils.c \
		ft_red_out_utils.c \
		ft_set_args_red.c \
		ft_redirection_utils.c \
		ft_redirections.c \
		echo.c \
		sorted_env.c \
		redirection_parse_utils.c \

OBJ = $(SRC:.c=.o)

PWD = ~/.brew/opt/readline
RLFLAGS =   -I $(PWD)/include\
            -lreadline\
            -L $(PWD)/lib\

CFLAGS = -Wall -Wextra -Werror -g

LIB = Libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -s -C ./Libft
	@$(MAKE) -s -C ./Libft bonus
	@ echo "libft compiled 🔋"
	@$(CC) $(CFLAGS) $(RLFLAGS) $(LIB) $(OBJ) -o $(NAME) -g3 -fsanitize=address
	@ echo "minishell compiled ☘︎"

%.o: %.c 
	$(CC) $(CFLAGS) -I $(PWD)/lib -c $< -o $@ -I $(PWD)/include

clean:
	@rm -rf minishell

fclean: clean
	@rm -rf minishell
	@rm -rf	minishell.dSYM
	@rm -rf libft/libft.a
	@rm -rf libft/*.o
	@rm -rf *.o
	@rm -rf .DStore
	@echo "libft cleaned🤘🏻"
	@echo "minishell cleaned🤘🏻"

re: fclean all

.PHONY : all clean fclean re
