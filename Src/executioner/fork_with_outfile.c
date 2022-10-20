/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_with_outfile.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:20:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/10/20 12:03:06 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	just_outfile_fork_process(t_node *command_table, t_vars *vars)
{	
	find_path(vars);
	vars->pid = fork();
	if (vars->pid == -1)
		perror("fork error\n");
	if (vars->pid == 0)
	{
		if (dup2(vars->f2, STDOUT_FILENO) == -1)
			print_error(command_table, vars);
		q_preform_cmd(command_table, vars);
	}
	else
		wait(&vars->pid);
}

void	just_outfile_multiple_fork_process(t_node *command_table, t_vars *vars)
{
	if (vars->append_open == 1)
		vars->f2 = open(vars->string_outfile, O_RDWR | O_APPEND);
	else
		vars->f2 = open(vars->string_outfile, \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars->f2 < 0)
		perror(vars->string_outfile);
	if (vars->com == 1)
		just_outfile_fork_process(command_table, vars);
	if (vars->com > 1)
		multiple_fork(command_table, vars);
	close(vars->f2);
}
