/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_one_com.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:20:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/11 14:40:00 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_out_file_one_command(t_node *command_table, t_vars *vars, \
									t_envp *env_list)
{
	int	status;

	find_path(vars);
	g_vars2.pid = fork();
	if (g_vars2.pid == -1)
		perror("fork error\n");
	if (g_vars2.pid == 0)
	{
		if (dup2(vars->f1, STDIN_FILENO) == -1)
			print_error(command_table, vars);
		if (dup2(vars->f2, STDOUT_FILENO) == -1)
			print_error(command_table, vars);
		close(vars->f1);
		close(vars->f2);
		q_preform_cmd(command_table, vars, env_list);
	}
	else
	{
		wait(&status);
		close(vars->f1);
		close(vars->f2);
		if (WIFEXITED(status))
			g_vars2.exitcode = WEXITSTATUS(status);
	}
}

void	just_infile_fork_process(t_node *command_table, t_vars *vars, \
									t_envp *env_list)
{
	int	status;

	find_path(vars);
	g_vars2.pid = fork();
	if (g_vars2.pid == -1)
		perror("fork error\n");
	if (g_vars2.pid == 0)
	{
		if (vars->f1 < 0)
			exit(1);
		if (dup2(vars->f1, STDIN_FILENO) == -1)
			print_error(command_table, vars);
		close(vars->f1);
		q_preform_cmd(command_table, vars, env_list);
	}
	else
	{
		wait(&status);
		close(vars->f1);
		if (WIFEXITED(status))
			g_vars2.exitcode = WEXITSTATUS(status);
	}
}

void	just_outfile_fork_process(t_node *command_table, t_vars *vars, \
										t_envp *env_list)
{	
	int	status;

	find_path(vars);
	g_vars2.pid = fork();
	if (g_vars2.pid == -1)
		perror("fork error\n");
	if (g_vars2.pid == 0)
	{
		if (dup2(vars->f2, STDOUT_FILENO) == -1)
			print_error(command_table, vars);
		close(vars->f2);
		q_preform_cmd(command_table, vars, env_list);
	}
	else
	{
		wait(&status);
		close(vars->f2);
		if (WIFEXITED(status))
			g_vars2.exitcode = WEXITSTATUS(status);
	}
}
