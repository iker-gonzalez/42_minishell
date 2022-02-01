NAME = minishell

SRC = test.c \

PWD = ~/.brew/opt/readline
RLFLAGS =   -I $(PWD)/include\
            -lreadline\
            -L $(PWD)/lib\

CFLAGS = -Wall -Wextra -Werror


all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(RLFLAGS) $^ -I $(SRC) -o $(NAME)
	@ echo "minishell compiled ☘︎"

%.o: %.c  $(SRC) $(SRCS)
	@$(CC) $(CFLAGS) -I $(PWD)/lib -I$(SRC) -c $< -o $@ -I $(PWD)/include

clean:
	@rm -rf minishell

fclean:
	@rm -rf minishell
	@rm -rf	minishell.dSYM
	@rm -rf .DStore
	@echo "minishell cleaned🤘🏻"

re: fclean all

.PHONY : all clean fclean re