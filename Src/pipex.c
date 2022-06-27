/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 12:16:31 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/06/27 11:45:52 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	preform_cmd(t_node *command_table, char**envp, t_vars *vars)
{
	vars->cmd = ft_split(command_table->content, ' ');
	if (!vars->cmd)
		print_error(vars);
	vars->path_cmd = ft_strdup(vars->cmd[0]);
	right_path(vars);
	if (execve(vars->my_path, vars->cmd, envp) < 0)
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
		commands_built(command_table, envp);
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
	while (command_table->next != '\0')
	{
		fork_proces(command_table, envp, vars);
		command_table = command_table->next;
	}
	commands_built(command_table, envp);
	preform_cmd(command_table, envp, vars);
	// if((commands_built(command_table, envp) == 0))	
	// 		preform_cmd(command_table, envp, vars);
}

void	pipex_start(t_node *command_table, char **envp)
{
	t_vars	vars;
	
	vars.f1 = open("infile", O_RDONLY, 0644);
	vars.f2 = open("outfile", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars.f1 < 0)
		print_error(&vars);
	if (vars.f2 < 0)
		print_error(&vars);
	find_path(envp, &vars);
	pipex(command_table, envp, &vars);
	close(vars.f1);
	close(vars.f2);
}
