/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:06:14 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/01 17:04:55 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*	
	kijken of infile in commmand_table staat.
		-zoja open dan infile en dub als STDIN
		-zonee dub pipe als STDIN (niet bij 1e)
	kijken of outfile in command_table staat.
		-zoja open outfile en dub als STDOUT
		-zonee Dub pipe als STDOUT(niet bij laatste)
	if in file close vars->f1 
	if outfile close vars->f2
*/ 

void	open_infile(t_vars *vars, t_node *command_table)
{
	vars->f1 = open(command_table->infile, O_RDONLY, 0644);
	if (vars->f1 < 0)
	{
		perror(command_table->infile);
		// exit(1);
		g_vars2.exitcode = 1;
	}
	if (dup2(vars->f1, STDIN_FILENO) == -1)
		print_error(command_table, vars);
}

void	open_outfile(t_vars *vars, t_node *command_table)
{
	if (command_table->append == 1)
		vars->f2 = open(command_table->outfile, O_RDWR | O_APPEND);
	else
		vars->f2 = open(command_table->outfile, \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars->f2 < 0)
	{
		perror(command_table->outfile);
		// exit(1);
		g_vars2.exitcode = 1;
	}
	if (dup2(vars->f2, STDOUT_FILENO) == -1)
		print_error(command_table, vars);
}

void	close_files(t_vars *vars, t_node *command_table)
{
	if (command_table->infile != NULL)
		close(vars->f1);
	if (command_table->outfile != NULL)
		close(vars->f2);
}

void	just_exit(int **fd, t_vars *vars, t_node *command_table)
{
	close_pipes(fd, vars);
	close_files(vars, command_table);
	exit(0);
}


void	first_child(t_node *command_table, int **fd, t_vars *vars, \
					t_envp *env_list)
{
	g_vars2.pid = fork();
	if (g_vars2.pid < 0)
		print_error(command_table, vars);
	if (g_vars2.pid == 0)
	{
		if (command_table->infile != NULL)
			open_infile(vars, command_table);
		if (command_table->outfile != NULL)
			open_outfile(vars, command_table);
		else
		{
			if (dup2(fd[0][1], STDOUT_FILENO) == -1)
				print_error(command_table, vars);
		}
		if (!command_table->command[0])
			just_exit(fd, vars, command_table);
		else
		{
			close_pipes(fd, vars);
			close_files(vars, command_table);
			q_preform_cmd(command_table, vars, env_list);
		}
	}
}

void	middle_child(t_node *command_table, int **fd, t_vars *vars, \
					t_envp *env_list)
{
	g_vars2.pid = fork();
	if (g_vars2.pid < 0)
		print_error(command_table, vars);
	if (g_vars2.pid == 0)
	{
		if (command_table->infile != NULL)
			open_infile(vars, command_table);
		else
			dup2(fd[vars->com_count - 1][0], STDIN_FILENO);
		if (command_table->outfile != NULL)
			open_outfile(vars, command_table);
		else
			dup2(fd[vars->com_count][1], STDOUT_FILENO);
		if (!command_table->command[0])
			just_exit(fd, vars, command_table);
		else
		{
			close_pipes(fd, vars);
			close_files(vars, command_table);
			q_preform_cmd(command_table, vars, env_list);
		}
	}
}

void	last_child(t_node *command_table, int **fd, t_vars *vars, \
					t_envp *env_list)
{
	g_vars2.pid = fork();
	if (g_vars2.pid < 0)
		print_error(command_table, vars);
	if (g_vars2.pid == 0)
	{
		if (command_table->infile != NULL)
			open_infile(vars, command_table);
		else
		{
			if (dup2(fd[vars->com_count - 1][0], STDIN_FILENO) == -1)
				print_error(command_table, vars);
		}
		if (command_table->outfile != NULL)
			open_outfile(vars, command_table);
		if (!command_table->command[0])
			just_exit(fd, vars, command_table);
		else
		{
			close_pipes(fd, vars);
			close_files(vars, command_table);
			q_preform_cmd(command_table, vars, env_list);
		}
	}
}
