/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/27 16:30:05 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_old_pwd(char *old, t_envp *temp)
{
	char	*old_content;

	while ((ft_strncmp("OLDPWD", temp->key, ft_strlen(temp->key)) != 0) && \
		temp->next != NULL)
		temp = temp->next;
	old_content = ft_strjoin("OLDPWD=", old);
	free(temp->content);
	temp->content = old_content;
}

static void	change_env_pwd(char *old, t_envp *list, t_vars *vars)
{
	char	new[PATH_MAX];
	char	*new_content;
	t_envp	*temp;
	t_envp	*temp2;

	temp = list;
	temp2 = list;
	getcwd(new, PATH_MAX);
	change_old_pwd(old, temp);
	while ((ft_strncmp("PWD", temp2->key, ft_strlen(temp2->key)) != 0) && \
			temp2->next != NULL)
		temp2 = temp2->next;
	new_content = ft_strjoin("PWD=", new);
	free(temp2->content);
	temp2->content = new_content;
	envp_to_array(list, vars);
}

static	char	*open_folder_utils(t_node *command_table, t_vars *vars, \
									t_envp *env)
{
	t_envp	*temp;
	char	*output;

	temp = env;
	output = NULL;
	if (command_table->command[1] == NULL)
	{
		while ((ft_strncmp("HOME", temp->key, ft_strlen(temp->key)) != 0) && \
			temp->next != NULL)
		temp = temp->next;
		output = temp->output;
	}
	else if (ft_strncmp(command_table->command[1], "-", 1) == 0)
	{
		if (vars->last_dir == NULL)
			ft_putstr_fd("Minishell: cd: No last directory", 2);
		else
			output = ft_strdup(vars->last_dir);
	}
	else
		output = command_table->command[1];
	return (output);
}

int	open_folder(t_node *command_table, t_envp *env, t_vars *vars)
{
	DIR				*dir;
	char			temp[PATH_MAX];
	char			*path;

	getcwd(temp, sizeof(temp));
	path = open_folder_utils(command_table, vars, env);
	if (command_table->command[1] != NULL)
	{
		dir = opendir(path);
		if (dir == NULL)
		{
			ft_putstr_fd("Minishell: cd: ", 2);
			perror(path);
		}
		if (dir != NULL)
			closedir(dir);
	}
	chdir(path);
	change_env_pwd(temp, env, vars);
	if (vars->last_dir != NULL)
		free(vars->last_dir);
	vars->last_dir = ft_strdup(temp);
	return (1);
}
