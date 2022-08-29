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

static void	q_preform_cmd(t_node *command_table, char**envp, t_vars *vars)
{
	if (!command_table->command)
		print_error(vars);
	right_path(vars, command_table);
	if (vars->my_path == NULL)
		pexit("nee", 1);
	if (execve(vars->my_path, command_table->command, envp) < 0)
		print_error(vars);
}

static void	q_fork_proces(t_node *command_table, char**envp, t_vars *vars)
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
		q_preform_cmd(command_table, envp, vars);
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

static void	q_pipex(t_node *command_table, char **envp, t_vars *vars)
{
	if (vars->no_file == 0)
	{
		if (dup2(vars->f1, STDIN_FILENO) == -1)
			print_error(vars);
		if (dup2(vars->f2, STDOUT_FILENO) == -1)
			print_error(vars);
	}
	if ((commands_built(command_table, envp) != 0))
	{
		while (command_table->next != NULL)
		{
			if (command_table->command[0] != NULL)
				q_fork_proces(command_table, envp, vars);
			command_table = command_table->next;
			// if (command_table->next->next == NULL && command_table->next->command[0] == NULL)
			// 	break;
			// if (command_table->next->next->next == NULL && command_table->next->next->command[0] == NULL)
			// {
			// 	command_table = command_table->next;
			// 	break;
			// }
			// else
			// 	command_table = command_table->next;
		}
	}
	q_preform_cmd(command_table, envp, vars);
}

// returnd de node met token infile om die door te geven aan open
char	*q_find_token_infile(t_node *command_table)
{
	t_node	*temp;
	
	temp = command_table;
	while (temp)
	{
		if (ft_strncmp(temp->infile , "", 1) != 0)
			return (temp->infile);
		temp = temp->next;
	}
	return ("");
}

// returnd node met token outfile om die door te geven aan open
char	*q_find_token_outfile(t_node *command_table)
{
	t_node	*temp;
	
	temp = command_table;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->outfile , "", 1) != 0)
			return (temp->outfile);
		temp = temp->next;
	}
	return ("");
}

void	q_pipex_start(t_node *command_table, char **envp)
{
	t_vars	vars;
	char	*string_infile;
	char	*string_outfile;

	string_infile = q_find_token_infile(command_table);
	string_outfile = q_find_token_outfile(command_table);
	vars.no_file = 0;
	printf("Dit is de infile = %s\n", string_infile);
	printf("Dit is de outfile = %s\n", string_outfile);
	if (ft_strncmp(string_infile , "", 1) != 0 && ft_strncmp(string_infile , "", 1) != 0)
	{
		vars.f1 = open(string_infile, O_RDONLY, 0644);
		vars.f2 = open(string_outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (vars.f1 < 0)
			print_error(&vars);
		if (vars.f2 < 0)
			print_error(&vars);
	}
	else
		vars.no_file = 1;
	find_path(envp, &vars);
	q_pipex(command_table, envp, &vars);
	close(vars.f1);
	close(vars.f2);
}
