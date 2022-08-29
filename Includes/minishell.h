/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:42:30 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/08/29 17:41:00 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <limits.h>


enum tokens {
	WORD = 1,
	OPTION = 2,
	LESS = 3,
	GREAT = 4,
	PIPE = 5,
	AMPERSAND = 6,
	NEWLINE = 7,
	GREATGREAT = 8,
	GREATAMPERSAND = 9,
	COMMAND = 10,
	INFILE = 11,
	OUTFILE = 12,
};

//pipex
typedef struct s_vars {
	int		f1;
	int		f2;
	int		no_file;
	char	**cmd;
	char	**path;
	char	*path_cmd;
	char	*my_path;
}				t_vars;

typedef struct s_node
{
	char			*content;
	char			*words;
	char			*infile;
	char			*outfile;
	char			*heredoc;
	char			**command;
	int				token;

	struct s_node	*next;
}	t_node;

void	command_table(char **split, char **envp);

void	list_print(t_node *list);
void	list_print_command(t_node *list);

// void	commands_built(t_node *command_table, char **envp);
int		commands_built(t_node *command_table, char **envp);

t_node	*create_list(char *head);
void	lstadd_back(t_node **lst, char *split, int token);
t_node	*create_head(char *first, int token);

//pipex
void	pipex_start(t_node *command_table, char **envp);
void	right_path(t_vars *vars, t_node *command_table);
void	find_path(char **envp, t_vars *vars);
void	print_error(t_vars *vars);
void	pexit(char *str, int exit_code);

// void	make_command_table(t_node *list, char **envp);
// t_node  *create_head_parser_pipe(t_node **list, t_node *command_table, int string_token, char *string);
// void	make_command_table_pipe(t_node *list, char **envp);

//lexer_utils
void	list_word(t_node **temp, char *word);
int		list_outfile(t_node **temp, char **outfile, int i);
int		list_infile(t_node **temp, char **infile, int i);
int 	list_single_quote(t_node **temp, char **pipe_split, int i);
int 	list_double_quote(t_node **temp, char **pipe_split, int i);

//quilfortpipex
void	q_pipex_start(t_node *command_table, char **envp);



#endif
