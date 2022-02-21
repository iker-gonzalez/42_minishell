NAME = minishell

SRC =	main.c \
		ft_execute.c \
		set_up.c \
		ft_read_input.c \
		ft_parse_input.c \
		ft_create_list.c \

OBJ = $(SRC:.c=.o)

PWD = ~/.brew/opt/readline
RLFLAGS =   -I $(PWD)/include\
            -lreadline\
            -L $(PWD)/lib\

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

LIB = Libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -s -C ./Libft
	@$(MAKE) -s -C ./Libft bonus
	@ echo "libft compiled 🔋"
	@$(CC) $(CFLAGS) $(RLFLAGS) $(LIB) $(OBJ) -o $(NAME)
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