/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 14:29:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/08/24 17:01:40 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_path(char **envp, t_vars *vars)
{
	char	*temp;

	while (ft_strncmp("PATH=", *envp, 5) && *(envp + 1))
		envp++;
	if (ft_strncmp("PATH=", *envp, 5) != 0)
		print_error(vars);
	temp = ft_strtrim(*envp, "PATH=");
	vars->path = ft_split(temp, ':');
	if (!vars->path)
		print_error(vars);
}

void	right_path(t_vars *vars, t_node *commands_table)
{
	char	*slash;
	char	*pipex_path;
	int		i;

	if (access(commands_table->command[0], X_OK) == 0)
		vars->my_path = ft_strdup(commands_table->command[0]);
	i = 0;
	while (vars->path[i] != '\0')
	{
		slash = ft_strjoin(vars->path[i], "/");
		if (!slash)
			print_error(vars);
		pipex_path = ft_strjoin(slash, commands_table->command[0]);
		if (!pipex_path)
			print_error(vars);
		if (access(pipex_path, X_OK) == 0)
			vars->my_path = ft_strdup(pipex_path);
		free(slash);
		free(pipex_path);
		i++;
	}
	if (!vars->my_path)
		pexit("Command not found", 127);
}
