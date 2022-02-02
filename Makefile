NAME = minishell

SRC =	main.c \

PWD = ~/.brew/opt/readline
RLFLAGS =   -I $(PWD)/include\
            -lreadline\
            -L $(PWD)/lib\

CFLAGS = -Wall -Wextra -Werror

LIB = Libft/libft.a


all: $(NAME)

$(NAME): $(SRC)
	@$(MAKE) -s -C ./Libft
	@$(MAKE) -s -C ./Libft bonus
	@ echo "libft compiled 🔋"
	@$(CC) $(CFLAGS) $(RLFLAGS) $(LIB) $^ -I $(SRC) -o $(NAME)
	@ echo "minishell compiled ☘︎"

%.o: %.c  $(SRC) $(SRCS)
	@$(CC) $(CFLAGS) -I $(PWD)/lib -I$(SRC) -c $< -o $@ -I $(PWD)/include

clean:
	@rm -rf minishell

fclean:
	@rm -rf minishell
	@rm -rf	minishell.dSYM
	@rm -rf libft/libft.a
	@rm -rf libft/*.o
	@rm -rf .DStore
	@echo "libft cleaned🤘🏻"
	@echo "minishell cleaned🤘🏻"

re: fclean all

.PHONY : all clean fclean re