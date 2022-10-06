/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executioner.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:33:18 by rharing       #+#    #+#                 */
/*   Updated: 2022/10/06 14:57:48 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	q_preform_cmd(t_node *command_table)
{
	if ((commands_built(command_table) == 0))
	{
		if (!command_table->command)
			print_error(command_table);
		right_path(command_table);
		if (!g_vars.my_path)
			print_error(command_table);
		if (execve(g_vars.my_path, command_table->command, \
			g_vars.enviroment) < 0)
			print_error(command_table);
	}
	else
		exit(0);
}

void	multiple_fork(t_node *command_table)
{
	int	fd[g_vars.com - 1][2];

	g_vars.com_count = 1;
	init_pipes(&fd);
	find_path();
	first_child(command_table, &fd);
	command_table = command_table->next;
	while (g_vars.com_count < (g_vars.com - 1))
	{
		middle_child(command_table, &fd);
		g_vars.com_count++;
		command_table = command_table->next;
	}
	last_child(command_table, &fd);
	close_pipes(&fd);
	ft_wait();
}

// is er geen outfile en infile en een command dan no_inoutfile functie
static	void	no_inoutfile(t_node *command_table)
{
	int	status;

	find_path();
	g_vars.pid = fork();
	if (g_vars.pid == -1)
		print_error(command_table);
	if (g_vars.pid == 0)
		q_preform_cmd(command_table);
	else
	{
		wait(&status);
		if (WIFSIGNALED(status))
		{
			printf("This is number 4 = %d\n\n", (WTERMSIG(status)));
			g_vars.exit_code = (WTERMSIG(status));
			g_vars.exit_code += 129;
		}
		if (WIFEXITED(status))
		{
			// printf("This is number 5 = %d\n\n", WEXITSTATUS(status));
			g_vars.exit_code = WEXITSTATUS(status);
		}
	}
}

void	q_pipex_start(t_node *command_table)
{
	g_vars.string_infile = q_find_token_infile(command_table);
	g_vars.string_outfile = q_find_token_outfile(command_table);
	g_vars.com = lstsize(command_table);
	if (g_vars.no_infile == 1 && g_vars.no_outfile == 1 && g_vars.com == 1)
		no_inoutfile(command_table);
	if (g_vars.no_infile == 1 && g_vars.no_outfile == 1 && g_vars.com > 1)
		multiple_fork(command_table);
	if (g_vars.no_infile == 0 && g_vars.no_outfile == 1)
		just_infile_multiple_fork_process(command_table);
	if (g_vars.no_infile == 1 && g_vars.no_outfile == 0)
		just_outfile_multiple_fork_process(command_table);
	if (g_vars.no_infile == 0 && g_vars.no_outfile == 0)
		in_out_file_fork_process(command_table);
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