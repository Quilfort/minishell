/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 11:28:56 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/03 15:00:11 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pexit(char *str, int exit_code)
{
	perror(str);
	g_vars.exit_code = exit_code;
	exit(exit_code);
}

void	print_error(t_node *command_table)
{
	if (g_vars.my_path == NULL)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command_table->command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_vars.exit_code = 127;
		exit(127);
	}
	g_vars.exit_code = 1;
	exit(1);
}
