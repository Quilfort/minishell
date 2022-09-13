/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_with_file.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:20:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/09/13 15:29:30 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	just_infile_fork_process(t_vars *vars, t_node *command_table, \
															char **envp)
{	
	find_path(envp, vars);
	vars->pid = fork();
	if (vars->pid == -1)
		print_error(vars);
	if (vars->pid == 0)
	{
		if (dup2(vars->f1, STDIN_FILENO) == -1)
			print_error(vars);
		q_preform_cmd(command_table, envp, vars);
	}
	else
		wait(&vars->pid);
}

// is er een infile en 1 command dan  open en justinfilefunctie
// is er een infile en meerdere commands dan open en multiplefork
void	just_infile_multiple_fork_process(t_vars *vars, t_node *command_table, \
																	char **envp)
{
	vars->f1 = open(vars->string_infile, O_RDONLY, 0644);
	if (vars->f1 < 0)
		print_error(vars);
	if (vars->com == 1)
		just_infile_fork_process(vars, command_table, envp);
	if (vars->com > 1)
		multiple_fork(command_table, envp, vars);
	close(vars->f1);
}

void	just_outfile_fork_process( t_vars *vars, t_node *command_table, \
															char **envp)
{	
	find_path(envp, vars);
	vars->pid = fork();
	if (vars->pid == 0)
	{
		if (dup2(vars->f2, STDOUT_FILENO) == -1)
			print_error(vars);
		q_preform_cmd(command_table, envp, vars);
	}
	else
		wait(&vars->pid);
}

// is er een outfile en 1 command dan open en justoutfilefunctie
// is er een outfile en meerdere commands dan open en multiplefork
void	just_outfile_multiple_fork_process(t_vars *vars, t_node *command_table, \
																	char **envp)
{
	vars->f2 = open(vars->string_outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars->f2 < 0)
		print_error(vars);
	if (vars->com == 1)
		just_outfile_fork_process(vars, command_table, envp);
	if (vars->com > 1)
		multiple_fork(command_table, envp, vars);
	close(vars->f2);
}

// is er een infile en outfile en meerdere commands open allebei en multiplefork
void	in_out_file_fork_process(t_vars *vars, t_node *command_table, \
															char **envp)
{
	vars->f1 = open(vars->string_infile, O_RDONLY, 0644);
	if (vars->f1 < 0)
		print_error(vars);
	vars->f2 = open(vars->string_outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars->f2 < 0)
		print_error(vars);
	multiple_fork(command_table, envp, vars);
	close(vars->f1);
	close(vars->f2);
}
