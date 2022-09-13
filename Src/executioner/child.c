/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:06:14 by rharing       #+#    #+#                 */
/*   Updated: 2022/09/13 15:55:52 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_child(t_vars *vars, t_node *command_table, \
					int (*fd)[vars->com][2], char **envp)
{
	int	pid1;

	pid1 = fork();
	if (pid1 < 0)
		print_error(vars);
	if (pid1 == 0)
	{
		if (vars->no_infile == 0)
		{
			if (dup2(vars->f1, STDIN_FILENO) == -1)
				print_error(vars);
		}
		dup2((*fd)[0][1], STDOUT_FILENO);
		close_pipes(vars, fd);
		q_preform_cmd(command_table, envp, vars);
	}
}

void	middle_child(t_vars *vars, t_node *command_table, \
					int (*fd)[vars->com][2], char **envp)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		print_error(vars);
	if (pid == 0)
	{
		dup2((*fd)[vars->com_count - 1][0], STDIN_FILENO);
		dup2((*fd)[vars->com_count][1], STDOUT_FILENO);
		close_pipes(vars, fd);
		q_preform_cmd(command_table, envp, vars);
	}
}

void	last_child(t_vars *vars, t_node *command_table, \
					int (*fd)[vars->com][2], char **envp)
{
	int	pid3;

	pid3 = fork();
	if (pid3 < 0)
		print_error(vars);
	if (pid3 == 0)
	{
		if (vars->no_outfile == 0)
		{
			if (dup2(vars->f2, STDOUT_FILENO) == -1)
				print_error(vars);
		}
		dup2((*fd)[vars->com_count - 1][0], STDIN_FILENO);
		close_pipes(vars, fd);
		q_preform_cmd(command_table, envp, vars);
	}
}
