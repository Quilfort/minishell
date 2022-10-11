/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:06:14 by rharing       #+#    #+#                 */
/*   Updated: 2022/10/11 14:22:55 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_child(t_node *command_table, int **fd)
{
	int	pid1;

	pid1 = fork();
	if (pid1 < 0)
		print_error(command_table);
	if (pid1 == 0)
	{
		if (g_vars.no_infile == 0)
		{
			if (dup2(g_vars.f1, STDIN_FILENO) == -1)
				print_error(command_table);
		}
		if (!command_table->command[0])
		{
			close_pipes(fd);
			exit(0);
		}
		else
		{
			dup2(fd[0][1], STDOUT_FILENO);
			close_pipes(fd);
			q_preform_cmd(command_table);
		}
	}
}

void	middle_child(t_node *command_table, int **fd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		print_error(command_table);
	if (pid == 0)
	{
		dup2(fd[g_vars.com_count - 1][0], STDIN_FILENO);
		dup2(fd[g_vars.com_count][1], STDOUT_FILENO);
		if (!command_table->command[0])
		{
			close_pipes(fd);
			exit(0);
		}
		else
		{
			close_pipes(fd);
			q_preform_cmd(command_table);
		}
	}
}

void	last_child(t_node *command_table, int **fd)
{
	int	pid3;

	pid3 = fork();
	if (pid3 < 0)
		print_error(command_table);
	if (pid3 == 0)
	{
		if (g_vars.no_outfile == 0)
		{
			if (dup2(g_vars.f2, STDOUT_FILENO) == -1)
				print_error(command_table);
		}
		if (!command_table->command[0])
		{
			close_pipes(fd);
			exit(0);
		}
		else
		{
			dup2(fd[g_vars.com_count - 1][0], STDIN_FILENO);
			close_pipes(fd);
			q_preform_cmd(command_table);
		}
	}
}
