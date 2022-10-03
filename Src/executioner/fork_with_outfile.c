/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_with_outfile.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:20:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/10/03 14:53:18 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	just_outfile_fork_process(t_node *command_table)
{	
	find_path();
	g_vars.pid = fork();
	if (g_vars.pid == -1)
		print_error(command_table);
	if (g_vars.pid == 0)
	{
		if (dup2(g_vars.f2, STDOUT_FILENO) == -1)
			print_error(command_table);
		q_preform_cmd(command_table);
	}
	else
		wait(&g_vars.pid);
}

// is er een outfile en 1 command dan open en justoutfilefunctie
// is er een outfile en meerdere commands dan open en multiplefork
void	just_outfile_multiple_fork_process(t_node *command_table)
{
	g_vars.f2 = open(g_vars.string_outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (g_vars.f2 < 0)
		perror(g_vars.string_outfile);
	if (g_vars.com == 1)
		just_outfile_fork_process(command_table);
	if (g_vars.com > 1)
		multiple_fork(command_table);
	close(g_vars.f2);
}
