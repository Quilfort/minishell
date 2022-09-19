// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   executioner.c                                      :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: rharing <rharing@student.42.fr>              +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2022/03/07 12:16:31 by qfrederi      #+#    #+#                 */
// /*   Updated: 2022/08/10 15:36:16 by rharing       ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "minishell.h"

static void	preform_cmd(t_node *command_table, char**envp, t_vars *vars)
{
	if (!command_table->command)
		print_error(vars);
	right_path(vars, command_table);
	if (vars->my_path == NULL)
		pexit("nee", 1);
	if (execve(vars->my_path, command_table->command, envp) < 0)
		print_error(vars);
}

static void	fork_proces(t_node *command_table, char**envp, t_vars *vars)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		print_error(vars);
	pid = fork();
	if (pid == -1)
		print_error(vars);
	if (pid == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			print_error(vars);
		// if ((commands_built(command_table, envp) == 0))
		// 	preform_cmd(command_table, envp, vars);

		// commands_built(command_table, envp);
		preform_cmd(command_table, envp, vars);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			print_error(vars);
	}
	close(pipefd[0]);
	close(pipefd[1]);
}

static void	pipex(t_node *command_table, char **envp, t_vars *vars)
{
	if (dup2(vars->f1, STDIN_FILENO) == -1)
		print_error(vars);
	if (dup2(vars->f2, STDOUT_FILENO) == -1)
		print_error(vars);
	if ((commands_built(command_table, envp) != 0))
	{
		while (command_table)
		{
			fork_proces(command_table, envp, vars);
			command_table = command_table->next;
		}
	}
	// preform_cmd(command_table, envp, vars);
}

// returnd de node met token infile om die door te geven aan open
char	*find_token_infile(t_node *command_table)
{
	while (command_table)
	{
		if (command_table->infile != NULL)
			return (command_table->infile);
		command_table = command_table->next;
	}
	return (NULL);
}

// returnd node met token outfile om die door te geven aan open
char	*find_token_outfile(t_node *command_table)
{
	while (command_table)
	{
		if (command_table->outfile != NULL)
			return (command_table->outfile);
			command_table = command_table->next;
	}
	return (NULL);
}

void	pipex_start(t_node *command_table, char **envp)
{
	t_vars	vars;
	char	*string_infile;
	char	*string_outfile;

	string_infile = find_token_infile(command_table);
	string_outfile = find_token_outfile(command_table);
	printf("\n dit%s \n dat%s", string_infile, string_outfile);
	vars.f1 = open(string_infile, O_RDONLY, 0644);
	vars.f2 = open(string_outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars.f1 < 0)
		print_error(&vars);
	if (vars.f2 < 0)
		print_error(&vars);
	find_path(envp, &vars);
	pipex(command_table, envp, &vars);
	close(vars.f1);
	close(vars.f2);
}
