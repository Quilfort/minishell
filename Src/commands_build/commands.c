/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/20 16:29:23 by rharing       ########   odam.nl         */
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
	char	*string_to_print;

	while (command_table->command[i] != '\0')
	{
		if (ft_strncmp(command_table->command[i], "<<", 2) == 0)
			ft_putstr_fd("", 1);
		i++;
	}
	string_to_print = ft_substr(command_table->words, 7, \
							ft_strlen(command_table->words));
	ft_putstr_fd(string_to_print, 1);
	free(string_to_print);
	return (1);
}

int	echo(t_node *command_table)
{
	int		i;
	char	*str_to_print;

	i = 2;
	if (!command_table->command[1])
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if (ft_strncmp("-n", command_table->command[1], 2) == 0)
		return (echo_n(command_table, i));
	else
	{
		i = 1;
		while (command_table->command[i] != '\0')
		{
			if (ft_strncmp(command_table->command[i], "<<", 2) == 0)
				ft_putstr_fd("", 1);
			i++;
		}
		str_to_print = ft_substr(command_table->words, 5, \
								ft_strlen(command_table->words));
		ft_putstr_fd(str_to_print, 1);
		ft_putchar_fd('\n', 1);
		free(str_to_print);
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
