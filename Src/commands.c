/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/08/30 18:09:56 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void error_exit(char *error_msg, int exit_code)
{
	perror(error_msg);
	exit(exit_code);
}

void	open_folder(t_node *command_table)
{
	DIR				*dir;
	struct dirent	*entry;

	command_table = command_table->next;
	dir = opendir(command_table->content);
	if (dir == NULL)
	{
		ft_putstr_fd("shell: cd: ", 2);
		perror(command_table->content); // als cd niet kan, dan doet bash dit, bv bash: cd: minishell: Not a directory, zonder exit
	}
	if (dir != NULL)
		closedir(dir);
	chdir(command_table->content);
}

void	echo(t_node *command_table)
{
	if (ft_strncmp("-n", command_table->next->content, 2) == 0)
	{
		command_table = command_table->next;
		command_table = command_table->next;
		while (command_table != NULL)
		{
			ft_putstr_fd(command_table->content, 1);
			ft_putchar_fd(' ', 1);
			command_table = command_table->next;
		}
	}
	else
	{
		command_table = command_table->next;
		while (command_table != NULL)
		{
			ft_putstr_fd(command_table->content, 1);
			ft_putchar_fd(' ', 1);
			command_table = command_table->next;
		}
		ft_putchar_fd('\n', 1);
	}
}

int	commands_built(t_node *command_table, char **envp)
{
	char	**split;
	int	i;
	int k;
	return (1);
	i = 2;
	split = ft_split(command_table->words, ' ');
	if ((ft_strncmp("exit", split[0], 4) == 0) && (split[1] == NULL))
	{
		ft_putendl_fd("exitcookies", 1);
		exit(0);
	}
	if ((ft_strncmp("pwd", split[0], 3) == 0) && (split[1] == NULL))
	{
		// getcwd zet path in string, met groote dus heb maar ff 2000 gemaakt.
		char string[PATH_MAX];
		getcwd(string, sizeof(string));
		ft_putendl_fd(string, 1);
		return (1);
	}
	if ((ft_strncmp("echo", command_table->content, 4) == 0))
	{
		// alles wat na de eerste node van command table komt wordt geprpint?
		if (command_table->next == NULL)
			ft_putchar_fd('\n', 1);
		else
			echo(command_table);
		return (1);
	}
	else if ((ft_strncmp("env", split[0], 3) == 0) && (split[1] == NULL))
	{
		k = 0;
		while(envp[k] != '\0')
		{
			ft_putendl_fd(envp[k], 1);
			k++;
		}
		return (1);
	}
	else if ((ft_strncmp("cd", command_table->content, 2) == 0))
	{
		open_folder(command_table);
		return (1);
	}
	return (0);
}