NAME = minishell
FLAGS = -Wall -Wextra -Werror -Wno-maybe-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter
SANITIZE = -fsanitize=address
VALGRIND = -g -Og -std=gnu99
READLINE = -lreadline
INC = -I%.h -I$(LIB_DIR)%.h

SRC_NAME =	main.c	\
		ft_cmd_exist.c	\

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAME))

LIB_DIR = ./libft/
#SRC_DIR = ./src/
OBJ_DIR = ./obj/

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) --silent
	@gcc $(FLAGS) $(SANITIZE) -o $(NAME) $(OBJ) -L $(LIB_DIR) -lft $(READLINE)
	@echo "##### minishell compiling finished! #####"

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@echo "##### Creating" [ $@ ] " #####"
	@gcc $(FLAGS) $(SANITIZE) -o $@ -c $< $(INC) $(READLINE)

clean:
	@make -C $(LIB_DIR) clean  --silent
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@echo "##### Removed object files #####"

fclean: clean
	@make -C $(LIB_DIR) fclean  --silent
	@rm -f $(NAME)
	@echo "##### Removed binary files #####"

re: fclean all

.PHONY: all clean fclean re
