/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/24 16:37:55 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **array, t_vars *vars)
{
	int		i;

	i = 0;
	array = malloc((vars->env_count + 1) * sizeof(char *));
	if (array == NULL)
		pexit("error", 1);
	while (i < vars->env_count)
	{
		array[i] = vars->enviroment[i];
		i++;
	}
	array[i + 1] = "\0";
	return (array);
}

int	arrlenght(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] != '\0') && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	sort_array(char **array, int arraylength)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < arraylength)
	{
		j = 0;
		while (j < arraylength - 1 - i)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
			{	
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	export_array(t_vars *vars)
{
	int		arraylength;

	vars->export_env = copy_env(vars->export_env, vars);
	arraylength = arrlenght(vars->export_env);
	sort_array(vars->export_env, arraylength);
}

void	export(t_envp *env_list, t_node *command_table, t_vars *vars)
{
	t_envp	*temp;

	free(vars->enviroment);
	lstadd_back_envp(&env_list, command_table->command[1]);
	envp_to_array(env_list, vars);
	temp = lstlast_envp(env_list);
	key_output(command_table->command[1], &temp);
	export_array(vars);
}
