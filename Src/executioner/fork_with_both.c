/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_with_both.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:20:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/10/03 14:52:50 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	in_out_file_one_command(t_node *command_table)
{
	find_path();
	g_vars.pid = fork();
	if (g_vars.pid == -1)
		print_error(command_table);
	if (g_vars.pid == 0)
	{
		if (dup2(g_vars.f1, STDIN_FILENO) == -1)
			print_error(command_table);
		if (dup2(g_vars.f2, STDOUT_FILENO) == -1)
			print_error(command_table);
		q_preform_cmd(command_table);
	}
	else
		wait(&g_vars.pid);
}

// is er een infile en outfile en meerdere commands open allebei en multiplefork
void	in_out_file_fork_process(t_node *command_table)
{
	g_vars.f1 = open(g_vars.string_infile, O_RDONLY, 0644);
	if (g_vars.f1 < 0)
		perror(g_vars.string_infile);
	if (g_vars.append_open == 1)
		g_vars.f2 = open(g_vars.string_outfile, O_RDWR | O_APPEND);
	else
		g_vars.f2 = open(g_vars.string_outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (g_vars.f2 < 0)
		perror(g_vars.string_outfile);
	if (g_vars.com == 1)
		in_out_file_one_command(command_table);
	else
		multiple_fork(command_table);
	close(g_vars.f1);
	close(g_vars.f2);
}
