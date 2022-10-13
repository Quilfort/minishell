/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_with_both.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:20:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/10/13 17:37:24 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	in_out_file_one_command(t_node *command_table, t_vars *vars)
{
	find_path(vars);
	vars->pid = fork();
	if (vars->pid == -1)
		perror("fork error\n");
	if (vars->pid == 0)
	{
		if (dup2(vars->f1, STDIN_FILENO) == -1)
			print_error(command_table, vars);
		if (dup2(vars->f2, STDOUT_FILENO) == -1)
			print_error(command_table, vars);
		q_preform_cmd(command_table, vars);
	}
	else
		wait(&vars->pid);
}

// is er een infile en outfile en meerdere commands open allebei en multiplefork
void	in_out_file_fork_process(t_node *command_table, t_vars *vars)
{
	vars->f1 = open(vars->string_infile, O_RDONLY, 0644);
	if (vars->f1 < 0)
		perror(vars->string_infile);
	if (vars->append_open == 1)
		vars->f2 = open(vars->string_outfile, O_RDWR | O_APPEND);
	else
		vars->f2 = open(vars->string_outfile, \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars->f2 < 0)
		perror(vars->string_outfile);
	if (vars->com == 1)
		in_out_file_one_command(command_table, vars);
	else
		multiple_fork(command_table, vars);
	close(vars->f1);
	close(vars->f2);
}
