/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 14:29:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/12 16:56:40 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_path(t_vars *vars)
{
	char	*temp;
	int		i;

	i = 0;
	while (ft_strncmp("PATH=", vars->enviroment[i], 5) \
			&& i + 1 < vars->env_count)
		i++;
	temp = ft_strtrim(vars->enviroment[i], "PATH=");
	vars->path = ft_split(temp, ':');
	if (!vars->path)
		perror("nopath");
	free(temp);
}

void	right_path(t_node *commands_table, t_vars *vars)
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
			print_error(commands_table, vars);
		pipex_path = ft_strjoin(slash, commands_table->command[0]);
		if (!pipex_path)
			print_error(commands_table, vars);
		if (access(pipex_path, X_OK) == 0)
			vars->my_path = ft_strdup(pipex_path);
		free(slash);
		free(pipex_path);
		i++;
	}
	if (vars->my_path == NULL)
		print_error(commands_table, vars);
}

char	*q_find_token_infile(t_node *command_table, t_vars *vars)
{
	t_node	*temp;

	vars->no_infile = 0;
	temp = command_table;
	while (temp)
	{
		if (temp->infile != NULL)
			return (temp->infile);
		temp = temp->next;
	}
	vars->no_infile = 1;
	return ("");
}

char	*q_find_token_outfile(t_node *command_table, t_vars *vars)
{
	t_node	*temp;

	vars->no_outfile = 0;
	temp = command_table;
	while (temp != NULL)
	{
		if (temp->outfile != NULL)
			return (temp->outfile);
		temp = temp->next;
	}
	vars->no_outfile = 1;
	return ("");
}
