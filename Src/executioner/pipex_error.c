/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 11:28:56 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/28 18:12:07 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pexit(char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
}

void	print_error(t_vars *vars, t_node *command_table)
{
	if (vars->my_path == NULL)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command_table->command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	exit(1);
}
