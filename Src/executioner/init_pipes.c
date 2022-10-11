/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_pipes.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:30:27 by rharing       #+#    #+#                 */
/*   Updated: 2022/10/11 14:31:43 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**malloc_pipes(void)
{
	int	**fd;
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = g_vars.com - 1;
	fd = (int **)malloc(pipe_count * sizeof(int *));
	while (i < pipe_count)
	{
		fd[i] = (int *)malloc(2 * sizeof(int));
		i++;
	}
	return (fd);
}

void	init_pipes(int **fd)
{
	int	x;

	x = 0;
	while (x < (g_vars.com - 1))
	{
		if (pipe(fd[x]) == -1)
			perror("error with pipes");
		x++;
	}
}

void	close_pipes(int **fd)
{
	int	j;

	j = 0;
	while (j < (g_vars.com - 1))
	{
		close(fd[j][0]);
		close(fd[j][1]);
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
	if (WIFSIGNALED(status))
		g_vars.exit_code = 130;
	else if (WIFEXITED(status))
		g_vars.exit_code = WEXITSTATUS(status);
}
