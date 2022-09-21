/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_built.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 14:47:35 by rharing       #+#    #+#                 */
/*   Updated: 2022/09/21 16:59:02 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	commands_built(t_node *command_table, t_vars *vars)
{
	if ((ft_strncmp("exit", command_table->command[0], 4) == 0) \
					&& (command_table->command[1] == NULL))
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	if ((ft_strncmp("pwd", command_table->command[0], 3) == 0) \
					&& (command_table->command[1] == NULL))
		return (pwd());
	if ((ft_strncmp("echo", command_table->content, 4) == 0))
		return (echo(command_table, vars));
	else if ((ft_strncmp("env", command_table->command[0], 3) == 0) \
						&& (command_table->command[1] == NULL))
		return (env(vars));
	else if ((ft_strncmp("cd", command_table->command[0], 2) == 0))
		return (open_folder(command_table));
	return (0);
}
