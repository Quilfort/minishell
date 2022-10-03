/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_to_array.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/03 14:51:32 by rharing       ########   odam.nl         */
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

// alleen nodig bij testen.
void	print_array(void)
{
	int	i;

	i = 0;
	while (i < g_vars.env_count)
	{
		printf("%s\n", g_vars.enviroment[i]);
		i++;
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
