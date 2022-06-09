/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/06/09 16:50:57 by qfrederi      ########   odam.nl         */
=======
/*   Updated: 2022/06/09 16:47:14 by rharing       ########   odam.nl         */
>>>>>>> b2c119f93346b1236c968fb98c981c8ab262bbed
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

	i = 0;
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
	parser();
	lexer();
	// write(1, "\n", 2);
	// open_folder(argv);
	return (0);
}
