/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/27 11:52:16 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_old_pwd(char *old, t_envp *list)
{
	char	*old_content;

	while ((ft_strncmp("OLDPWD", list->key, ft_strlen(list->key)) != 0) && \
		list->next != NULL)
	{
		list = list->next;
	}
	old_content = ft_strjoin("OLDPWD=", old);
	// free(list->content);
	list->content = old_content;
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
	// printf("\nThis is old PWD = %s\n\n", old);
	// printf("\nThis is new PWD = %s\n\n", new);
	change_old_pwd(old, temp);
	// while ((ft_strncmp("PWD", list->key, ft_strlen(list->key)) != 0) && \
	// 		list->next != NULL)
	// 	list = list->next;
	// free(list->content);
	// list->content = new_content;
	while ((ft_strncmp("PWD", temp2->key, ft_strlen(temp2->key)) != 0) && \
			temp2->next != NULL)
		temp2 = temp2->next;
	new_content = ft_strjoin("PWD=", new);
	temp2->content = new_content;
	envp_to_array(list, vars);
}

static	void	open_folder_utils(t_node *command_table, char *last_dir)
{
	if (command_table->command[1] == NULL)
		command_table->command[1] = getenv("HOME");
	else if (ft_strncmp(command_table->command[1], "-", 1) == 0)
	{
		if (last_dir == NULL)
			ft_putstr_fd("Minishell: cd: No last directory", 2);
		command_table->command[1] = ft_strdup(last_dir);
	}
}

int	open_folder(t_node *command_table, t_envp *env, t_vars *vars)
{
	DIR				*dir;
	char			*last_dir;
	char			temp[PATH_MAX];

	last_dir = NULL;
	getcwd(temp, sizeof(temp));
	open_folder_utils(command_table, last_dir);
	if (command_table->command[1] != NULL)
	{
		dir = opendir(command_table->command[1]);
		if (dir == NULL)
		{
			ft_putstr_fd("Minishell: cd: ", 2);
			perror(command_table->command[1]);
		}
		if (dir != NULL)
			closedir(dir);
	}
	chdir(command_table->command[1]);
	change_env_pwd(temp, env, vars);
	last_dir = ft_strdup(temp);
	return (1);
}
