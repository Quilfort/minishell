/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 11:28:56 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/06/27 10:49:17 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_vars *vars)
{
	if (vars->f1 < 0 || vars->f2 < 0)
	{
		perror("Can't Open It");
		exit(1);
	}
	if (vars->my_path == NULL)
	{
		perror("Command not found");
		exit(127);
	}
	else
		perror("Error: 404s and Heartbreak");
	exit(1);
}
