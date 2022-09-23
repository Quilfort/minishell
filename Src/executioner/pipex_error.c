/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 11:28:56 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/08/24 15:03:13 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pexit(char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
}

void	print_error(t_vars *vars)
{
	if (vars->my_path == NULL)
	{
		perror("Command not found");
		exit(127);
	}
	else if (vars->f1 < 0 || vars->f2 < 0)
	{
		perror("Can't Open It");
		exit(1);
	}
	else
		perror("Error: 404s and Heartbreak");
	exit(1);
}
