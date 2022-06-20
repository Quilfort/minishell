NAME = minishell
LIBFT_DIR = ./Libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
FLAGS = -Wall -Wextra -Werror -lreadline
INC = -I ./Includes
SRC = ./Src/main.c ./Src/list.c \
	./Src/lexer.c
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc $(OBJ) $(LIBFT) $(FLAGS) -o $(NAME)

%.o: %.c
	gcc $(INC) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
.PHONY: all clean fclean re