/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_to_array.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/12 10:42:25 by qfrederi      ########   odam.nl         */
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
		free(temp);
	}
}

void	envp_to_array(t_envp *env)
{
	int	i;
	int	count;

	count = lst_size(env);
	i = 0;
	g_vars.enviroment = malloc((count) * sizeof(char *));
	if (g_vars.enviroment == NULL)
		pexit("error", 1);
	while (i < count)
	{
		g_vars.enviroment[i] = ft_strdup(env->content);
		i++;
		env = env->next;
	}
	g_vars.enviroment[i + 1] = "\0";
	g_vars.env_count = i;
}
