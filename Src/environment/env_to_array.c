/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_to_array.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/27 16:37:06 by qfrederi      ########   odam.nl         */
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

void	envp_to_array(t_envp *env, t_vars *vars)
{
	int		i;
	int		count;

	count = lst_size(env);
	i = 0;
	vars->enviroment = malloc((count + 1) * sizeof(char *));
	if (vars->enviroment == NULL)
		pexit("error", 1);
	while (i < count)
	{
		vars->enviroment[i] = env->content;
		i++;
		env = env->next;
	}
	vars->enviroment[i] = NULL;
	vars->env_count = count;
}
