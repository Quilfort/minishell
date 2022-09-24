/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_pipes.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:30:27 by rharing       #+#    #+#                 */
/*   Updated: 2022/09/13 15:31:14 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipes(t_vars *vars, int (*fd)[vars->com - 2][2])
{
	int	x;

	x = 0;
	while (x < (vars->com - 1))
	{
		if (pipe((*fd)[x]) == -1)
			perror("error with pipes");
		x++;
	}
}

void	close_pipes(t_vars *vars, int (*fd)[vars->com - 2][2])
{
	int	j;

	j = 0;
	while (j < (vars->com - 1))
	{
		close((*fd)[j][0]);
		close((*fd)[j][1]);
		j++;
	}
}

void	ft_wait(t_vars *vars)
{
	int	x;

	x = 0;
	while (x < vars->com)
	{
		wait(NULL);
		x++;
	}
}
