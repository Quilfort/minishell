NAME = minishell
LIBFT_DIR = ./Libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
FLAGS = -Wall -Wextra -Werror -lreadline -g -fsanitize=address
INC = -I ./Includes 
EXEC_FOLDER = ./src/executioner/
COMMANDS_FOLDER = ./src/commands_build/
ENVIRONMENT_FOLDER = ./src/environment/
SRC = ./src/main.c \
	./src/lexer.c \
	./src/lexer_utils.c \
	./src/list.c \
	./src/signals.c \
	$(ENVIRONMENT_FOLDER)envp_list.c \
	$(ENVIRONMENT_FOLDER)env_var.c \
	$(COMMANDS_FOLDER)commands_built.c \
	$(COMMANDS_FOLDER)commands.c \
	$(EXEC_FOLDER)child.c \
	$(EXEC_FOLDER)executioner.c \
	$(EXEC_FOLDER)get_path.c \
	$(EXEC_FOLDER)fork_with_file.c \
	$(EXEC_FOLDER)init_pipes.c \
	$(EXEC_FOLDER)pipex_error.c
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