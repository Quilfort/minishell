/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 11:03:47 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/17 18:10:30 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_command(t_node *list)
{
	t_node	*temp;
	size_t	i;

	while (list != NULL)
	{
		i = 0;
		temp = list;
		free(temp->words);
		free(temp->content);
		free(temp->heredoc);
		free(temp->infile);
		free(temp->outfile);
		while (temp->command[i] != NULL)
		{
			free(temp->command[i]);
			i++;
		}
		free(temp->command);
		free(temp);
		list = list->next;
	}
}

void	freepipes(int **fd, t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->com - 1)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
