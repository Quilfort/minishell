/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_to_array.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/13 16:11:12 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	lst_size(t_envp *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

void	free_envp(t_envp *list)
{
	t_envp	*temp;

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		free(temp->content);
		free(temp->key);
		free(temp->output);
		free(temp);
	}
}

void	envp_to_array(t_envp *env, t_vars *vars)
{
	int	i;
	int	count;

	count = lst_size(env);
	i = 0;
	vars->enviroment = malloc((count + 1) * sizeof(char *));
	if (vars->enviroment == NULL)
		pexit("error", 1);
	while (i < count)
	{
		vars->enviroment[i] = ft_strdup(env->content);
		i++;
		env = env->next;
	}
	vars->enviroment[i + 1] = "\0";
	vars->env_count = i;
}
