/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 14:29:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/06/27 13:54:24 by qfrederi      ########   odam.nl         */
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

char	*right_path(t_vars *vars)
{
	char	*slash;
	char	*pipex_path;
	int		i;

	if (access(vars->path_cmd, X_OK) == 0)
		return (vars->my_path = ft_strdup(vars->path_cmd));
	i = 0;
	while (vars->path[i] != '\0')
	{
		slash = ft_strjoin(vars->path[i], "/");
		if (!slash)
			print_error(vars);
		pipex_path = ft_strjoin(slash, vars->path_cmd);
		if (!pipex_path)
			print_error(vars);
		if (access(pipex_path, X_OK) == 0)
			vars->my_path = ft_strdup(pipex_path);
		free(slash);
		free(pipex_path);
		i++;
	}
	if (!vars->my_path)
		print_error(vars);
	return (vars->my_path);
}
