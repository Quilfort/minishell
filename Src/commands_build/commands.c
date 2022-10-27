/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/27 11:23:56 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("declare -x %s\n", array[i]);
		i++;
	}
}

int	builtin(t_node *command_table, t_envp *env, t_vars *vars)
{
	if ((ft_strncmp("export", command_table->command[0], 6) == 0) \
		&& ft_strlen("export") == ft_strlen(command_table->command[0]))
	{
		if (command_table->command[1] != NULL)
			export(env, command_table, vars);
		else
			print_array(vars->export_env);
		return (1);
	}
	else if ((ft_strncmp("cd", command_table->command[0], 2) == 0) \
		&& ft_strlen("cd") == ft_strlen(command_table->command[0]))
	{
		open_folder(command_table, env, vars);
		return (1);
	}
	else if ((ft_strncmp("unset", command_table->command[0], 3) == 0) \
		&& (command_table->command[1] != NULL) \
		&& ft_strlen("unset") == ft_strlen(command_table->command[0]))
	{
		unset(env, command_table, vars);
		return (1);
	}
	return (0);
}

int	commands_built(t_node *command_table, t_vars *vars)
{
	if ((ft_strncmp("pwd", command_table->command[0], 3) == 0) \
		&& (command_table->command[1] == NULL) \
		&& ft_strlen("pwd") == ft_strlen(command_table->command[0]))
		return (pwd());
	else if ((ft_strncmp("echo", command_table->command[0], 4) == 0) \
		&& ft_strlen("echo") == ft_strlen(command_table->command[0]))
		return (echo(command_table, vars));
	else if ((ft_strncmp("env", command_table->command[0], 3) == 0) \
		&& (command_table->command[1] == NULL) \
		&& ft_strlen("env") == ft_strlen(command_table->command[0]))
		return (env(vars));
	return (0);
}

int	pwd(void)
{
	char	string[PATH_MAX];

	getcwd(string, sizeof(string));
	ft_putendl_fd(string, 1);
	return (0);
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
