/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_with_outfile.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:20:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/01 17:14:34 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	just_outfile_multiple_fork_process(t_node *command_table, t_vars *vars, \
											t_envp *env_list)
{
	if (vars->com == 1)
	{
		just_outfile_fork_process(command_table, vars, env_list);
		close(vars->f2);
	}
	if (vars->com > 1)
		multiple_fork(command_table, vars, env_list);
}
