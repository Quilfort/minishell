/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/09 16:58:09 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/06/09 17:05:03 by qfrederi      ########   odam.nl         */
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

void	parser()
{
	char			*input;
	char			**cmd;

	while (1)
	{
		input = readline("Q-Shell: ");
		add_history(input);
		printf("%s", input);
		printf("\n");
		cmd = ft_split(input, ' ');
		if ((ft_strncmp("pwd", cmd[0], 3) == 0) && (cmd[1] == NULL))
		{
			system("pwd");
		}
		if ((ft_strncmp("env", cmd[0], 3) == 0) && (cmd[1] == NULL))
		{
			system("env");
		}
		if ((ft_strncmp("exit", cmd[0], 4) == 0) && (cmd[1] == NULL))
		{
			exit(0);
		}
	}
}
// asdfjsdfjawfoj

// je moederasdf.
int	main(int argc, char *argv[])
{
	// parser();
	lexer();
	// write(1, "\n", 2);
	// open_folder(argv);
	return (0);
}
