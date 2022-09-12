NAME = minishell
LIBFT_DIR = ./Libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
FLAGS = -Wall -Wextra -Werror -lreadline -g -fsanitize=address
INC = -I ./Includes 
SRC = ./Src/main.c \
	./Src/lexer.c \
	./Src/lexer_utils.c \
	./Src/list.c \
	./Src/envp_list.c \
	./Src/env_var.c \
	./Src/commands.c \
	./Src/q_executioner.c \
	./Src/get_path.c \
	./Src/pipex_error.c
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
	rm -rf $(NAME)
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
.PHONY: all clean fclean re