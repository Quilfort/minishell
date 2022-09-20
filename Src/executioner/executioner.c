/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executioner.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:33:18 by rharing       #+#    #+#                 */
/*   Updated: 2022/09/20 16:44:20 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	q_preform_cmd(t_node *command_table, t_vars *vars)
{
	if (!command_table->command)
		print_error(vars);
	right_path(vars, command_table);
	if (vars->my_path == NULL)
		pexit("nee", 1);
	if (execve(vars->my_path, command_table->command, vars->enviroment) < 0)
		print_error(vars);
}

void	multiple_fork(t_node *command_table, t_vars *vars)
{
	int	fd[vars->com - 1][2];

	vars->com_count = 1;
	init_pipes(vars, &fd);
	find_path(vars);
	first_child(vars, command_table, &fd);
	command_table = command_table->next;
	while (vars->com_count < (vars->com - 1))
	{
		middle_child(vars, command_table, &fd);
		vars->com_count++;
		command_table = command_table->next;
	}
	last_child(vars, command_table, &fd);
	close_pipes(vars, &fd);
	ft_wait(vars);
}

// is er geen outfile en infile en een command dan no_inoutfile functie
static	void	no_inoutfile(t_node *command_table, t_vars *vars)
{
	find_path(vars);
	vars->pid = fork();
	if (vars->pid == -1)
		print_error(vars);
	if (vars->pid == 0)
		q_preform_cmd(command_table, vars);
	else
		wait(&vars->pid);
}

void	q_pipex_start(t_node *command_table, t_vars *vars)
{
	vars->string_infile = q_find_token_infile(command_table, vars);
	vars->string_outfile = q_find_token_outfile(command_table, vars);
	vars->com = lstsize(command_table);
	if (vars->no_infile == 1 && vars->no_outfile == 1 && vars->com == 1)
		no_inoutfile(command_table, vars);
	if (vars->no_infile == 1 && vars->no_outfile == 1 && vars->com > 1)
		multiple_fork(command_table, vars);
	if (vars->no_infile == 0 && vars->no_outfile == 1)
		just_infile_multiple_fork_process(vars, command_table);
	if (vars->no_infile == 1 && vars->no_outfile == 0)
		just_outfile_multiple_fork_process(vars, command_table);
	if (vars->no_infile == 0 && vars->no_outfile == 0)
		in_out_file_fork_process(vars, command_table);
}

/*
	de logica:
		-	is er een infile en 1 command dan  open en justinfilefunctie
		- 	is er een infile en meerdere commands dan open en multiplefork
		- 	is er een outfile en 1 command dan open en justoutfilefunctie
		- 	is er een outfile en meerdere commands dan open en multiplefork
		-	is er een infile en outfile en meerdere commands open allebei en multiplefork
		-	is er een infile en outfile en een command open en wat dan??
		-	is er geen outfile en infile en een command dan no_inoutfile functie
		- 	is er geen outfile en infile en meerdere commands dan multiplefork
*/