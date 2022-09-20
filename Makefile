NAME = minishell
LIBFT_DIR = ./Libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
# BREW_DIR = $(shell brew --prefix)
# LIB_READLINE = $(BREW_DIR)/opt/readline/lib
# INCLUDE_READLINE = -I $(BREW_DIR)/opt/readline/include
# READLINE_DIRS = -L $(LIB_READLINE) $(READLINE)
FLAGS = -Wall -Wextra -Werror -lreadline -g -fsanitize=address
INC = -I ./Includes
SIGNAL_FOLDER = ./src/signals/
PARSING_FOLDER = ./src/parsing/
EXEC_FOLDER = ./src/executioner/
COMMANDS_FOLDER = ./src/commands_build/
ENVIRONMENT_FOLDER = ./src/environment/
SRC = ./src/main.c \
	$(SIGNAL_FOLDER)signals.c \
	$(PARSING_FOLDER)here_doc.c \
	$(PARSING_FOLDER)create_command_table.c \
	$(PARSING_FOLDER)lexer_utils.c \
	$(PARSING_FOLDER)lexer.c \
	$(PARSING_FOLDER)list.c \
	$(PARSING_FOLDER)quotes.c \
	$(ENVIRONMENT_FOLDER)env_to_array.c \
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