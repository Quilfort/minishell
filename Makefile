NAME = minishell
LIBFT_DIR = ./Libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
FLAGS = -Wall -Wextra -Werror -lreadline -g -fsanitize=address
INC = -I ./Includes 
EXEC_MAP = ./src/executioner/
SRC = ./src/main.c \
	./src/lexer.c \
	./src/lexer_utils.c \
	./src/list.c \
	./src/envp_list.c \
	./src/env_var.c \
	./src/commands.c \
	./src/signals.c \
	$(EXEC_MAP)child.c \
	$(EXEC_MAP)executioner.c \
	$(EXEC_MAP)get_path.c \
	$(EXEC_MAP)fork_with_file.c \
	$(EXEC_MAP)init_pipes.c \
	$(EXEC_MAP)pipex_error.c
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