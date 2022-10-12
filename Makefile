NAME = minishell
LIBFT_DIR = ./Libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
FLAGS = -Wall -Wextra -Werror -lreadline
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
	$(PARSING_FOLDER)interpreter_utils.c \
	$(PARSING_FOLDER)interpreter.c \
	$(PARSING_FOLDER)list.c \
	$(PARSING_FOLDER)quotes.c \
	$(PARSING_FOLDER)words.c \
	$(ENVIRONMENT_FOLDER)env_to_array.c \
	$(ENVIRONMENT_FOLDER)envp_list.c \
	$(ENVIRONMENT_FOLDER)env_var.c \
	$(COMMANDS_FOLDER)cd.c \
	$(COMMANDS_FOLDER)commands.c \
	$(COMMANDS_FOLDER)echo.c \
	$(COMMANDS_FOLDER)export.c \
	$(COMMANDS_FOLDER)unset.c \
	$(EXEC_FOLDER)child.c \
	$(EXEC_FOLDER)executioner.c \
	$(EXEC_FOLDER)get_path.c \
	$(EXEC_FOLDER)fork_with_both.c \
	$(EXEC_FOLDER)fork_with_infile.c \
	$(EXEC_FOLDER)fork_with_outfile.c \
	$(EXEC_FOLDER)init_pipes.c \
	$(EXEC_FOLDER)pipex_error.c
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc $(OBJ) $(LIBFT) $(FLAGS) -L /Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include -o $(NAME)

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