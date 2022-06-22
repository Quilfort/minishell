/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/06/22 14:36:35 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void error_exit(char *error_msg, int exit_code)
{
	perror(error_msg);
	exit(exit_code);
}

void	open_folder(char *split)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(split);
	if (dir == NULL)
	{
		ft_putstr_fd("shell: cd: ", 2);
		perror(split); // als cd niet kan, dan doet bash dit, bv bash: cd: minishell: Not a directory, zonder exit
	}
	if (dir != NULL)
		closedir(dir);
	chdir(split);
}

// echo appart in functie gezet
void	echo(char **split, int i)
{
	if(ft_strncmp("-n", split[1], 2) == 0)
	{
		while (split[i] != '\0')
		{
			ft_putstr_fd(split[i], 1);
			i++;
			if (split[i] != '\0')
				ft_putchar_fd(' ', 1);
		}
	}
	else
	{
		i = 1;
		while (split[i] != '\0')
		{
			ft_putstr_fd(split[i], 1);
			i++;
			if (split[i] != '\0')
				ft_putchar_fd(' ', 1);
		}
		ft_putchar_fd('\n', 1);
	}
}

// void	commands(char **split, char **envp)
// {
// 		int	i;
// 		int k;

// 		i = 2;
// 		if ((ft_strncmp("exit", split[0], 4) == 0) && (split[1] == NULL))
// 		{
// 			exit(0);
// 		}
// 		if ((ft_strncmp("pwd", split[0], 3) == 0) && (split[1] == NULL))
// 		{
// 			// getcwd zet path in string, met groote dus heb maar ff 2000 gemaakt.
// 			char string[PATH_MAX];
// 			getcwd(string, sizeof(string));
// 			ft_putendl_fd(string, 1);
// 		}
// 		else if ((ft_strncmp("echo", split[0], 4) == 0) && (split[1] != NULL))
// 		{
// 			echo(split, i);
// 		}
// 		else if ((ft_strncmp("env", split[0], 3) == 0) && (split[1] == NULL))
// 		{
// 			k = 0;
// 			while(envp[k] != '\0')
// 			{
// 				ft_putendl_fd(envp[k], 1);
// 				k++;
// 			}
// 		}
// 		else if ((ft_strncmp("cd", split[0], 2) == 0) && (split[1] != NULL))
// 		{
// 			open_folder(split[1]);
// 		}
// }

void	commands_built(t_node *command_table, char **envp)
{
	char	**split;
	int	i;
	int k;

	i = 2;
	while (command_table != NULL)
	{
		split = ft_split(command_table->content, ' ');
			if ((ft_strncmp("exit", split[0], 4) == 0) && (split[1] == NULL))
		{
			exit(0);
		}
		if ((ft_strncmp("pwd", split[0], 3) == 0) && (split[1] == NULL))
		{
			// getcwd zet path in string, met groote dus heb maar ff 2000 gemaakt.
			char string[PATH_MAX];
			getcwd(string, sizeof(string));
			ft_putendl_fd(string, 1);
		}
		else if ((ft_strncmp("echo", split[0], 4) == 0) && (split[1] != NULL))
		{
			echo(split, i);
		}
		else if ((ft_strncmp("env", split[0], 3) == 0) && (split[1] == NULL))
		{
			k = 0;
			while(envp[k] != '\0')
			{
				ft_putendl_fd(envp[k], 1);
				k++;
			}
		}
		else if ((ft_strncmp("cd", split[0], 2) == 0) && (split[1] != NULL))
		{
			open_folder(split[1]);
		}
		command_table = command_table->next;
	}
}