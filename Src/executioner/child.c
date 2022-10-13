/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:06:14 by rharing       #+#    #+#                 */
/*   Updated: 2022/10/13 17:36:13 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_child(t_node *command_table, int **fd, t_vars *vars)
{
	int	pid1;

	pid1 = fork();
	if (pid1 < 0)
		print_error(command_table, vars);
	if (pid1 == 0)
	{
		if (vars->no_infile == 0)
		{
			if (dup2(vars->f1, STDIN_FILENO) == -1)
				print_error(command_table, vars);
		}
		if (!command_table->command[0])
		{
			close_pipes(fd, vars);
			exit(0);
		}
		else
		{
			dup2(fd[0][1], STDOUT_FILENO);
			close_pipes(fd, vars);
			q_preform_cmd(command_table, vars);
		}
	}
}

void	middle_child(t_node *command_table, int **fd, t_vars *vars)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		print_error(command_table, vars);
	if (pid == 0)
	{
		dup2(fd[vars->com_count - 1][0], STDIN_FILENO);
		dup2(fd[vars->com_count][1], STDOUT_FILENO);
		if (!command_table->command[0])
		{
			close_pipes(fd, vars);
			exit(0);
		}
		else
		{
			close_pipes(fd, vars);
			q_preform_cmd(command_table, vars);
		}
	}
}

void	last_child(t_node *command_table, int **fd, t_vars *vars)
{
	int	pid3;

	pid3 = fork();
	if (pid3 < 0)
		print_error(command_table, vars);
	if (pid3 == 0)
	{
		if (vars->no_outfile == 0)
		{
			if (dup2(vars->f2, STDOUT_FILENO) == -1)
				print_error(command_table, vars);
		}
		if (!command_table->command[0])
		{
			close_pipes(fd, vars);
			exit(0);
		}
		else
		{
			dup2(fd[vars->com_count - 1][0], STDIN_FILENO);
			close_pipes(fd, vars);
			q_preform_cmd(command_table, vars);
		}
	}
}
