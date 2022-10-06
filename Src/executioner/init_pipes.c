/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_pipes.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:30:27 by rharing       #+#    #+#                 */
/*   Updated: 2022/10/06 12:13:32 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipes(int (*fd)[g_vars.com - 2][2])
{
	int	x;

	x = 0;
	while (x < (g_vars.com - 1))
	{
		if (pipe((*fd)[x]) == -1)
			perror("error with pipes");
		x++;
	}
}

void	close_pipes(int (*fd)[g_vars.com - 2][2])
{
	int	j;

	j = 0;
	while (j < (g_vars.com - 1))
	{
		close((*fd)[j][0]);
		close((*fd)[j][1]);
		j++;
	}
}

void	ft_wait(void)
{
	int	x;
	int	status;

	x = 0;
	while (x < g_vars.com)
	{
		wait(&status);
		x++;
	}
	if (WIFEXITED(status))
		g_vars.exit_code = WEXITSTATUS(status);
}
