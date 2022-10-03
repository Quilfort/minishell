/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_with_infile.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:20:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/10/03 14:53:05 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	just_infile_fork_process(t_node *command_table)
{
	find_path();
	g_vars.pid = fork();
	if (g_vars.pid == -1)
		print_error(command_table);
	if (g_vars.pid == 0)
	{
		if (dup2(g_vars.f1, STDIN_FILENO) == -1)
			print_error(command_table);
		q_preform_cmd(command_table);
	}
	else
		wait(&g_vars.pid);
}

// is er een infile en 1 command dan  open en justinfilefunctie
// is er een infile en meerdere commands dan open en multiplefork
void	just_infile_multiple_fork_process(t_node *command_table)
{
	g_vars.f1 = open(g_vars.string_infile, O_RDONLY, 0644);
	if (g_vars.f1 < 0)
		perror(g_vars.string_infile);
	if (g_vars.com == 1)
		just_infile_fork_process(command_table);
	if (g_vars.com > 1)
		multiple_fork(command_table);
	close(g_vars.f1);
}
