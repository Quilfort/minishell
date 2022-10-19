/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:42:30 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/19 14:01:03 by qfrederi      ########   odam.nl         */
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
# include <sys/signal.h>
# include <dirent.h>
# include <limits.h>
# include <termios.h>

extern int	g_exitcode;

//pipex
typedef struct s_vars {
	int		f1;
	int		f2;
	int		no_infile;
	int		no_outfile;
	int		env_count;
	char	**enviroment;
	char	**cmd;
	char	**path;
	char	*path_cmd;
	char	*my_path;
	char	*string_infile;
	char	*string_outfile;
	int		com;
	int		com_count;
	int		append_open;
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

void	main_loop(int flag, t_envp *env, t_vars *vars);
void	free_command(t_node *list);

// Commands_build
		// cd.c
int		open_folder(t_node *command_table);

		// commands.c
int		commands_built(t_node *command_table, t_vars *vars);
int		builtin(t_node *command_table, t_envp *env, t_vars *vars);
int		pwd(void);
int		env(t_vars *vars);

		//echo.c
int		echo(t_node *command_table, t_vars *vars);

		// export.c
void	export(t_envp *env_list, t_node *command_table, t_vars *vars);

		// unset.c
void	unset(t_envp *env_list, t_node *command_table, t_vars *vars);

// environment
		// env_to_array.c
int		lst_size(t_envp *list);
void	print_array(void);
void	envp_to_array(t_envp *env, t_vars *vars);
void	free_envp(t_envp *list);

		// env_var.c
void	print_envp(t_envp *list);
char	*env_var(t_envp *list, char *var);
void	key_output(char *split, t_envp **temp);

		// envp list
t_envp	*lstlast_envp(t_envp *lst);
void	lstadd_back_envp(t_envp **lst, char *split);
t_envp	*create_head_envp(char *first);
t_envp	*put_envp_in_list(char **envp);

// executioner
		// executioner.c
void	q_preform_cmd(t_node *command_table, t_vars *vars);
void	multiple_fork(t_node *command_table, t_vars *vars);
void	q_pipex_start(t_node *command_table, t_vars *vars);

		// child.c
void	first_child(t_node *command_table, int **fd, t_vars *vars);
void	middle_child(t_node *command_table, int **fd, t_vars *vars);
void	last_child(t_node *command_table, int **fd, t_vars *vars);

		// fork_with_both.c
void	in_out_file_fork_process(t_node *command_table, t_vars *vars);

		// fork_with_infile.c
void	just_infile_multiple_fork_process(t_node *command_table, t_vars *vars);

		// fork_with_outfile.c
void	just_outfile_multiple_fork_process(t_node *command_table, t_vars *vars);

		// get_path.c
void	right_path(t_node *command_table, t_vars *vars);
void	find_path(t_vars *vars);
char	*q_find_token_infile(t_node *command_table, t_vars *vars);
char	*q_find_token_outfile(t_node *command_table, t_vars *vars);

		// init_pipes.c
int		**malloc_pipes(t_vars *vars);
void	init_pipes(int **fd, t_vars *vars);
void	close_pipes(int **fd, t_vars *vars);
void	ft_wait(t_vars *vars);

		// pipex_error.c
void	print_error(t_node *command_table, t_vars *vars);
void	pexit(char *str, int exit_code);

// parsing
		// create_command_table.c
void	exec_init(t_node *command_table);
t_node	*create_command_table_list(char *split, t_envp *env, t_vars *vars);
void	command_table(char *split, t_envp *env, t_vars *vars);
int		make_pipes(char *split, int i);
int		add_to_list(t_node *node, int i, char *split);

		// here_doc.c
int		list_heredoc(t_node **temp, char *split, int i, t_envp *env);

		// here_doc_utils.c
char	*delimiter_without_quotes(char *delimiter);

		// interpreter_util.c
int		list_outfile(t_node **temp, int i, char *split);
int		list_infile(t_node **temp, int i, char *split);
int		find_var(t_node **temp, int i, char *split, t_envp *env);
int		var_first_char(char *split, int i, t_node **temp);

		// interpreter.c
void	list_print_command(t_node *list);
int		redirect_infile(t_node *temp, char *split, int i);
int		redirect_here_doc(t_node *temp, char *split, int i, t_envp *env);
int		redirect_outfile(t_node *temp, char *split, int i, t_vars *vars);
void	split_pipe(char *split, t_node *temp, t_envp *env, t_vars *vars);

		// list.c
int		lstsize(t_node *list);
void	lstadd_back(t_node **lst, char *split);
t_node	*create_head(char *first);

		// quotes.c
void	add_to_word(t_node **temp, char *word);
int		find_quote(t_node **temp, int i, char *split, int start);
int		list_double_quote(t_node **temp, int i, char *split, t_envp *env);
int		list_single_quote(t_node **temp, int i, char *split, t_envp *env);
int		var_in_double_quotes(t_node **temp, int i, char *split, t_envp *env);

		// words.c
int		split_word(t_node **temp, int i, char *split, t_envp *env);
int		find_word(t_node **temp, int i, char *split, int start);
void	add_to_word_split(t_node **temp, char *word, int space);
void	add_space(t_node **temp, char *split, int start);

// signals
void	signals(void);

//free
void	freesplit(char **split);
void	free_command(t_node *list);
void	freepipes(int **fd, t_vars *vars);

#endif