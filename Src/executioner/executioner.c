/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executioner.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:33:18 by rharing       #+#    #+#                 */
/*   Updated: 2022/10/13 16:12:54 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	q_preform_cmd(t_node *command_table, t_vars *vars)
{
	if ((commands_built(command_table, vars) == 0))
	{
		if (!command_table->command)
			print_error(command_table, vars);
		right_path(command_table, vars);
		// printf("this is my path = %s\n\n", vars->my_path);
		// printf("this is my command = %s\n\n", command_table->command[0]);
		// printf("this is my env = %s\n\n", vars->enviroment[0]);
		if (!vars->my_path)
			print_error(command_table, vars);
		if (execve(vars->my_path, command_table->command, \
			vars->enviroment) < 0)
			print_error(command_table, vars);
	}
	else
		exit(0);
}

void	multiple_fork(t_node *command_table, t_vars *vars)
{
	int	**fd;

	fd = malloc_pipes(vars);
	vars->com_count = 1;
	init_pipes(fd, vars);
	find_path(vars);
	first_child(command_table, fd, vars);
	command_table = command_table->next;
	while (vars->com_count < (vars->com - 1))
	{
		middle_child(command_table, fd, vars);
		vars->com_count++;
		command_table = command_table->next;
	}
	last_child(command_table, fd, vars);
	close_pipes(fd, vars);
	ft_wait(vars);
}

static	void	no_inoutfile(t_node *command_table, t_vars *vars)
{
	int	status;

	find_path(vars);
	vars->pid = fork();
	if (vars->pid == -1)
		perror("fork error\n");
	if (vars->pid == 0)
		q_preform_cmd(command_table, vars);
	else
	{
		signal(SIGINT, SIG_IGN);
		wait(&status);
		if (WIFSIGNALED(status))
			g_exitcode = 130;
		if (WIFEXITED(status))
			g_exitcode = WEXITSTATUS(status);
		signals();
	}
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
		just_infile_multiple_fork_process(command_table, vars);
	if (vars->no_infile == 1 && vars->no_outfile == 0)
		just_outfile_multiple_fork_process(command_table, vars);
	if (vars->no_infile == 0 && vars->no_outfile == 0)
		in_out_file_fork_process(command_table, vars);
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