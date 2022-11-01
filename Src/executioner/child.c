/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:06:14 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/01 17:04:55 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_child(t_node *command_table, int **fd, t_vars *vars, \
					t_envp *env_list)
{
	g_vars2.pid = fork();
	if (g_vars2.pid < 0)
		print_error(command_table, vars);
	if (g_vars2.pid == 0)
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
			q_preform_cmd(command_table, vars, env_list);
		}
	}
}

void	middle_child(t_node *command_table, int **fd, t_vars *vars, \
					t_envp *env_list)
{
	g_vars2.pid = fork();
	if (g_vars2.pid < 0)
		print_error(command_table, vars);
	if (g_vars2.pid == 0)
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
			q_preform_cmd(command_table, vars, env_list);
		}
	}
}

void	last_child(t_node *command_table, int **fd, t_vars *vars, \
					t_envp *env_list)
{
	g_vars2.pid = fork();
	if (g_vars2.pid < 0)
		print_error(command_table, vars);
	if (g_vars2.pid == 0)
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
			q_preform_cmd(command_table, vars, env_list);
		}
	}
}
