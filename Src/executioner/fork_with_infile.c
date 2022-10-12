/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_with_infile.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:20:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/10/12 15:23:18 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	just_infile_fork_process(t_node *command_table, t_vars *vars)
{
	find_path(vars);
	vars->pid = fork();
	if (vars->pid == -1)
		perror("fork error\n");
	if (vars->pid == 0)
	{
		if (dup2(vars->f1, STDIN_FILENO) == -1)
			print_error(command_table, vars);
		q_preform_cmd(command_table, vars);
	}
	else
		wait(&vars->pid);
}

// is er een infile en 1 command dan  open en justinfilefunctie
// is er een infile en meerdere commands dan open en multiplefork
void	just_infile_multiple_fork_process(t_node *command_table, t_vars *vars)
{
	vars->f1 = open(vars->string_infile, O_RDONLY, 0644);
	if (vars->f1 < 0)
		perror(vars->string_infile);
	if (vars->com == 1)
		just_infile_fork_process(command_table, vars);
	if (vars->com > 1)
		multiple_fork(command_table, vars);
	close(vars->f1);
}
