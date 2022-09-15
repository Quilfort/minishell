/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:42:30 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/15 17:27:14 by qfrederi      ########   odam.nl         */
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
	int		no_infile;
	int		no_outfile;
	char	**cmd;
	char	**path;
	char	*path_cmd;
	char	*my_path;
	char	*string_infile;
	char	*string_outfile;
	int		com;
	int		com_count;
	pid_t	pid;
}	t_vars;

//input to commands
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

//envp in list
typedef struct s_envp
{
	char			*content;
	char			*key;
	char			*output;

	struct s_envp	*next;
}	t_envp;

void	command_table(char **split, char **envp, t_envp *env);
int 	list_heredoc(t_node **temp, char **pipe_split, int i, t_envp *env);

void	list_print(t_node *list);
void	list_print_command(t_node *list);

// void	commands_built(t_node *command_table, char **envp);
int		commands_built(t_node *command_table, t_envp *list_envp, char **envp);

t_node	*create_list(char *head);
void	lstadd_back(t_node **lst, char *split);
t_node	*create_head(char *first);

// environment
		// env_var.c
void	print_envp(t_envp *list);
char	*env_var(t_envp *list, char *var);
void	key_output(char *split, t_envp **temp);

		// envp list
void	lstadd_back_envp(t_envp **lst, char *split, int token);
t_envp	*create_head_envp(char *first);

// executioner
		// executioner.c
void	q_preform_cmd(t_node *command_table, char**envp, t_vars *vars);
void	multiple_fork(t_node *command_table, char **envp, t_vars *vars);
void	pipex_start(t_node *command_table, char **envp);
void	q_pipex_start(t_node *command_table, char **envp);

		// child.c
void	first_child(t_vars *vars, t_node *command_table, \
					int (*fd)[vars->com][2], char **envp);
void	middle_child(t_vars *vars, t_node *command_table, \
					int (*fd)[vars->com][2], char **envp);
void	last_child(t_vars *vars, t_node *command_table, \
					int (*fd)[vars->com][2], char **envp);

		// fork_with_file.c
void	just_infile_fork_process(t_vars *vars, t_node *command_table, \
															char **envp);	
void	just_infile_multiple_fork_process(t_vars *vars, t_node *command_table, \
															char **envp);
void	just_outfile_fork_process( t_vars *vars, t_node *command_table, \
															char **envp);
void	just_outfile_multiple_fork_process(t_vars *vars, t_node *command_table, \
															char **envp);
void	in_out_file_fork_process(t_vars *vars, t_node *command_table, \
															char **envp);

		// get_path.c
void	right_path(t_vars *vars, t_node *command_table);
void	find_path(char **envp, t_vars *vars);
char	*q_find_token_infile(t_node *command_table, t_vars *vars);
char	*q_find_token_outfile(t_node *command_table, t_vars *vars);

		// init_pipes.c
void	init_pipes(t_vars *vars, int (*fd)[vars->com - 2][2]);
void	close_pipes(t_vars *vars, int (*fd)[vars->com - 2][2]);
void	ft_wait(t_vars *vars);

		// pipex_error.c
void	print_error(t_vars *vars);
void	pexit(char *str, int exit_code);

// Commands_build
		// commands_built.c
int		commands_built(t_node *command_table, t_envp *list_envp, char **envp);	

		// commands.c
int		open_folder(t_node *command_table);
int		echo(t_node *command_table);
int		pwd(void);
int		env(t_envp *list_envp);

//lexer_utils
int		lstsize(t_node *list);
void	list_word(t_node **temp, char *word);
int		list_outfile(t_node **temp, char **outfile, int i);
int		list_infile(t_node **temp, char **infile, int i);
int 	list_single_quote(t_node **temp, char **pipe_split, int i, t_envp *env);
int		list_double_quote(t_node **temp, char **pipe_split, int i, t_envp *env);

// signals
void	signals(void);

#endif
