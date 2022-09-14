/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/14 14:53:01 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_folder(t_node *command_table)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(command_table->command[1]);
	if (dir == NULL)
	{
		ft_putstr_fd("shell: cd: ", 2);
		perror(command_table->command[1]);
	}
	if (dir != NULL)
		closedir(dir);
	chdir(command_table->command[1]);
	return (1);
}

static	int	echo_n(t_node *command_table, int i)
{
	while (command_table->command[i] != '\0')
	{
		if (ft_strncmp(command_table->command[i], "<<", 2) == 0)
			ft_putstr_fd(command_table->heredoc, 1);
		else
			ft_putstr_fd(command_table->command[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	return (1);
}

int	echo(t_node *command_table)
{
	int	i;

	i = 2;
	if (ft_strncmp("-n", command_table->command[1], 2) == 0)
		return (echo_n(command_table, i));
	else
	{
		i = 1;
		while (command_table->command[i] != '\0')
		{
			if (ft_strncmp(command_table->command[i], "<<", 2) == 0)
				ft_putstr_fd(command_table->heredoc, 1);
			else
				ft_putstr_fd(command_table->command[i], 1);
			ft_putchar_fd(' ', 1);
			i++;
		}
		ft_putchar_fd('\n', 1);
	}
	return (1);
}

int	pwd(void)
{
	char	string[PATH_MAX];

	getcwd(string, sizeof(string));
	ft_putendl_fd(string, 1);
	return (1);
}

int	env(t_envp *list_envp)
{
	while (list_envp != NULL)
	{
		ft_putendl_fd(list_envp->content, 1);
		list_envp = list_envp->next;
	}
	return (1);
}
