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

static  void	open_folder_utils(t_node *command_table, char *last_dir)
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

int	open_folder(t_node *command_table)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*last_dir;
	char			temp[PATH_MAX];

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
	last_dir = ft_strdup(temp);
	return (1);
}
