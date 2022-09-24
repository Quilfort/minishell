/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 14:29:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/21 15:57:56 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_path(t_vars *vars)
{
	char	*temp;
	int		i;

	i = 0;
	while (ft_strncmp("PATH=", vars->enviroment[i], 5) && i + 1 < vars->env_count)
		i++;
	// if (i == vars->env_count)
	// 	ft_putstr_fd("Error", 2);
	// if (ft_strncmp("PATH=", vars->enviroment[i], 5) != 0)
	// 	ft_putstr_fd("Error", 2);
	temp = ft_strtrim(vars->enviroment[i], "PATH=");
	// temp = getenv("PATH");
	vars->path = ft_split(temp, ':');
	if (!vars->path)
		perror("nopath");
}

void	right_path(t_vars *vars, t_node *commands_table)
{
	char	*slash;
	char	*pipex_path;
	int		i;

	vars->my_path = NULL;
	if (access(commands_table->command[0], X_OK) == 0)
		vars->my_path = ft_strdup(commands_table->command[0]);
	i = 0;
	while (vars->path[i] != '\0')
	{
		slash = ft_strjoin(vars->path[i], "/");
		if (!slash)
			print_error(vars, commands_table);
		pipex_path = ft_strjoin(slash, commands_table->command[0]);
		if (!pipex_path)
			print_error(vars, commands_table);
		if (access(pipex_path, X_OK) == 0)
			vars->my_path = ft_strdup(pipex_path);
		free(slash);
		free(pipex_path);
		i++;
	}
	if (!vars->my_path)
		print_error(vars, commands_table);
}

// returnd de node met token infile om die door te geven aan open
char	*q_find_token_infile(t_node *command_table, t_vars *vars)
{
	t_node	*temp;

	vars->no_infile = 0;
	temp = command_table;
	while (temp)
	{
		if (ft_strncmp(temp->infile, "", 1) != 0)
			return (temp->infile);
		temp = temp->next;
	}
	vars->no_infile = 1;
	return ("");
}

// returnd node met token outfile om die door te geven aan open
char	*q_find_token_outfile(t_node *command_table, t_vars *vars)
{
	t_node	*temp;

	vars->no_outfile = 0;
	temp = command_table;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->outfile, "", 1) != 0)
			return (temp->outfile);
		temp = temp->next;
	}
	vars->no_outfile = 1;
	return ("");
}
