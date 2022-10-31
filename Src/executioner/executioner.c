/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executioner.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:33:18 by rharing       #+#    #+#                 */
/*   Updated: 2022/10/31 15:20:53 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	q_preform_cmd(t_node *command_table, t_vars *vars)
{
	if ((ft_strncmp("exit", command_table->command[0], 4) == 0) \
		&& ft_strlen("exit") == ft_strlen(command_table->command[0]))
		exit_program(command_table);
	else if ((commands_built(command_table, vars) == 0))
	{
		if (!command_table->command)
			print_error(command_table, vars);
		right_path(command_table, vars);
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
	freepipes(fd, vars);
}

static	void	no_inoutfile(t_node *command_table, t_vars *vars)
{
	int	status;

	find_path(vars);
	g_vars2.pid = fork();
	if (g_vars2.pid == -1)
		perror("fork error\n");
	if (g_vars2.pid == 0)
		q_preform_cmd(command_table, vars);
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			g_vars2.exitcode = WEXITSTATUS(status);
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
