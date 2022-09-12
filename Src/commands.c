/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/12 14:29:17 by qfrederi      ########   odam.nl         */
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


	dir = opendir(command_table->command[1]);
	if (dir == NULL)
	{
		ft_putstr_fd("shell: cd: ", 2);
		perror(command_table->command[1]); // als cd niet kan, dan doet bash dit, bv bash: cd: minishell: Not a directory, zonder exit
	}
	if (dir != NULL)
		closedir(dir);
	chdir(command_table->command[1]);
}

void	echo(t_node *command_table)
{
	int i;

	i = 2;
	if (ft_strncmp("-n", command_table->command[1], 2) == 0)
	{
		while (command_table->command[i] != '\0')
		{
		
			if (ft_strncmp(command_table->command[i], "<<", 2) == 0)
			{
				ft_putstr_fd(command_table->heredoc, 1);
			}
			else
				ft_putstr_fd(command_table->command[i], 1);
			ft_putchar_fd(' ', 1);
			i++;
		}
	}
	else
	{
		i = 1;
		while (command_table->command[i] != '\0')
		{
			if (ft_strncmp(command_table->command[i], "<<", 2) == 0)
			{
				ft_putstr_fd(command_table->heredoc, 1);
			}
			else
				ft_putstr_fd(command_table->command[i], 1);
			ft_putchar_fd(' ', 1);
			i++;
		}
		ft_putchar_fd('\n', 1);
	}
}

int	commands_built(t_node *command_table, char **envp)
{
	int k;

	if ((ft_strncmp("exit", command_table->command[0], 4) == 0) && (command_table->command[1] == NULL))
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	if ((ft_strncmp("pwd", command_table->command[0], 3) == 0) && (command_table->command[1] == NULL))
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
		echo(command_table);
		return (1);
	}
	else if ((ft_strncmp("env", command_table->command[0], 3) == 0) && (command_table->command[1] == NULL))
	{
		k = 0;
		while(envp[k] != '\0')
		{
			ft_putendl_fd(envp[k], 1);
			k++;
		}
		return (1);
	}
	else if ((ft_strncmp("cd", command_table->command[0], 2) == 0))
	{
		open_folder(command_table);
		return (1);
	}
	return (0);
}