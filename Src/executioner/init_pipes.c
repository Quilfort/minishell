/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_pipes.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:30:27 by rharing       #+#    #+#                 */
/*   Updated: 2022/10/13 17:39:34 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**malloc_pipes(t_vars *vars)
{
	int	**fd;
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = vars->com - 1;
	fd = (int **)malloc(pipe_count * sizeof(int *));
	while (i < pipe_count)
	{
		fd[i] = (int *)malloc(2 * sizeof(int));
		i++;
	}
	return (fd);
}

void	init_pipes(int **fd, t_vars *vars)
{
	int	x;

	x = 0;
	while (x < (vars->com - 1))
	{
		if (pipe(fd[x]) == -1)
			perror("error with pipes");
		x++;
	}
}

void	close_pipes(int **fd, t_vars *vars)
{
	int	j;

	j = 0;
	while (j < (vars->com - 1))
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
}

void	ft_wait(t_vars *vars)
{
	int	x;
	int	status;

	x = 0;
	while (x < vars->com)
	{
		wait(&status);
		x++;
	}
	if (WIFSIGNALED(status))
		g_exitcode = 130;
	else if (WIFEXITED(status))
		g_exitcode = WEXITSTATUS(status);
}
