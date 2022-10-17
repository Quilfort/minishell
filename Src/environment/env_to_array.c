/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_to_array.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/17 18:18:44 by rharing       ########   odam.nl         */
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
// void	print_array(t_vars *vars)
// {
// 	int	i;

// 	i = 0;
// 	while (i < vars->env_count)
// 	{
// 		printf("%s\n", vars->enviroment[i]);
// 		i++;
// 	}
// }

void	envp_to_array(t_envp *env, t_vars *vars)
{
	int		i;
	int		count;
	char	*temp;

	count = lst_size(env);
	printf("dit is lstcount: %d\n", count);
	i = 0;
	vars->enviroment = malloc((count + 1) * sizeof(char *));
	if (vars->enviroment == NULL)
		pexit("error", 1);
	while (i < count)
	{
		vars->enviroment[i] = env->content;
		printf("dit is listconten: %s", env->content);
		printf("dis is i: %d\n", i);
		i++;
		env = env->next;
	}
	vars->enviroment[i + 1] = "\0";
	vars->env_count = count;
}
