/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/06/15 12:45:39 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_folder(char *argv[])
{
	DIR				*dir;
	struct dirent	*entry;
	int				files;

	files = 0;
	dir = opendir("Src");
	if (dir == NULL)
	{
		printf("Couldn't open dir\n");
		exit (1);
	}
	while((entry = readdir(dir)))
	{
		files++;
		printf("File %3d: %s\n", files, entry->d_name);
	}
	if (dir != NULL)
		closedir(dir);
}

void	commands(char **split)
{
		if ((ft_strncmp("exit", split[0], 4) == 0) && (split[1] == NULL))
		{
			exit(0);
		}
		else if ((ft_strncmp("pwd", split[0], 3) == 0) && (split[1] == NULL))
		{
			system("pwd");
		}
		else if ((ft_strncmp("echo", split[0], 4) == 0) && (ft_strncmp("-n", split[1], 2) == 0))
		{
			ft_putstr_fd(split[2], 1);
		}
		else if ((ft_strncmp("env", split[0], 3) == 0) && (split[1] == NULL))
		{
			system("env");
		}
		else
			lexer(split);
}

int	main(int argc, char *argv[])
{
	char			*input;
	char			**split;

	while (1)
	{
		input = readline("Minishell QR1.0: ");
		add_history(input);
		split = ft_split(input, ' ');
		commands(split);
	}
	return (0);
}

// QUILFORT'S TEST TO BRANCHE