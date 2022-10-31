/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/31 18:23:37 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*get_node_oldpwd(t_envp *env_list)
{
	t_envp	*temp;

	temp = env_list;
	while (temp != NULL)
	{
		if ((ft_strncmp("OLDPWD", temp->key, ft_strlen(temp->key)) == 0))
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

t_envp	*get_node_pwd(t_envp *env_list)
{
	t_envp	*temp;

	temp = env_list;
	while (temp != NULL)
	{
		if ((ft_strncmp("PWD", temp->key, ft_strlen(temp->key)) == 0))
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

static void	change_old_pwd(t_envp *temp, char *old_content, t_envp *list)
{
	if (temp)
		refill_node(temp, old_content);
	else
	{
		lstadd_back_envp(&list, old_content);
		temp = lstlast_envp(list);
		key_output(old_content, &temp);
	}
}

static void	change_env_pwd(char *old, t_envp *list, t_vars *vars)
{
	char	new[PATH_MAX];
	char	*new_content;
	char	*old_content;
	t_envp	*temp;

	getcwd(new, PATH_MAX);
	new_content = ft_strjoin("PWD=", new);
	old_content = ft_strjoin("OLDPWD=", old);
	temp = get_node_pwd(list);
	if (temp)
		refill_node(temp, new_content);
	else
	{
		lstadd_back_envp(&list, new_content);
		temp = lstlast_envp(list);
		key_output(new_content, &temp);
	}
	temp = get_node_oldpwd(list);
	change_old_pwd(temp, old_content, list);
	envp_to_array(list, vars);
	free(new_content);
	free(old_content);
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
			output = vars->last_dir;
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
	if (path != NULL)
	{
		dir = opendir(path);
		if (dir == NULL)
		{
			ft_putstr_fd("Minishell: cd: ", 2);
			perror(path);
		}
		if (dir != NULL)
			closedir(dir);
		chdir(path);
		change_env_pwd(temp, env, vars);
		if (vars->last_dir != NULL)
			free(vars->last_dir);
		vars->last_dir = ft_strdup(temp);
	}
	return (1);
}
