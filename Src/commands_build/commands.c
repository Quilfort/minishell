/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/21 17:13:32 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	commands_built(t_node *command_table, t_vars *vars)
{
	if ((ft_strncmp("pwd", command_table->command[0], 3) == 0) \
					&& (command_table->command[1] == NULL))
		return (pwd());
	if ((ft_strncmp("echo", command_table->content, 4) == 0))
		return (echo(command_table, vars));
	if ((ft_strncmp("env", command_table->command[0], 3) == 0) \
						&& (command_table->command[1] == NULL))
		return (env(vars));
	return (0);
}

int	pwd(void)
{
	char	string[PATH_MAX];

	getcwd(string, sizeof(string));
	ft_putendl_fd(string, 1);
	return (1);
}

int	env(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->env_count)
	{
		ft_putendl_fd(vars->enviroment[i], 1);
		i++;
	}
	return (1);
}
