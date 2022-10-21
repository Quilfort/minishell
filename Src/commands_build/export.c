/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/19 13:51:59 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **copy_env(char **array, t_vars *vars)
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
	return(array);
}

int	arrlenght(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return(i);
}

void	sort_array(char **array, int arraylength)
{
	int i;
	int j;
	char *temp;

	i = 0;
	while(i < arraylength)
	{
		j = 0;
		while (j < arraylength - 1 - i)
		{
			if(ft_strncmp(array[j], array[j+1], ft_strlen(array[j])) > 0)
			{	
       	 		temp = array[j];
       		 	array[j] = array[j + 1];
       		 	array[j+1] = temp;
      		}
			j++;
		}
		i++;
	}
}

void	print_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		printf("declare -x %s\n", array[i]);
		i++;
	}
}

void	export_array(t_vars *vars)
{
	char **array;
	int arraylength;

	array = NULL;
	array = copy_env(array, vars);
	arraylength = arrlenght(array);
	sort_array(array, arraylength);
	print_array(array);
	free(array);
}

void	export(t_envp *env_list, t_node *command_table, t_vars *vars)
{
	t_envp	*temp;

	free(vars->enviroment);
	lstadd_back_envp(&env_list, command_table->command[1]);
	envp_to_array(env_list, vars);
	temp = lstlast_envp(env_list);
	key_output(command_table->command[1], &temp);
}
