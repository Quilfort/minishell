/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_with_infile.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:20:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/01 17:13:05 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	just_infile_fork_process(t_node *command_table, t_vars *vars, \
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
		q_preform_cmd(command_table, vars, env_list);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			g_vars2.exitcode = WEXITSTATUS(status);
	}
}

void	just_infile_multiple_fork_process(t_node *command_table, t_vars *vars, \
											t_envp *env_list)
{
	if (vars->com == 1)
		just_infile_fork_process(command_table, vars, env_list);
	if (vars->com > 1)
		multiple_fork(command_table, vars, env_list);
	close(vars->f1);
}
