/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/31 17:01:12 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_env(t_vars *vars, t_envp *env)
{
	int		i;
	int		count;

	i = 0;
	count = lst_size(env);
	vars->export_env = malloc((count + 1) * sizeof(char *));
	if (vars->export_env == NULL)
		pexit("error", 1);
	while (i < count)
	{
		vars->export_env[i] = ft_strdup(env->content);
		i++;
		env = env->next;
	}
	vars->export_env[i] = NULL;
	return (count);
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

void	export_array(t_vars *vars, t_envp *env)
{
	int		arraylength;

	if (vars->export_env != NULL)
		freesplit(vars->export_env);
	arraylength = copy_env(vars, env);
	sort_array(vars->export_env, arraylength);
}

int		get_key_lenght(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '=' && string[i] != '\0')
		i++;
	return (i);
}

t_envp	*get_node(t_envp *env_list, char *string)
{
	t_envp	*temp;
	char	*trim;
	int		key_lenght;

	temp = env_list;
	key_lenght = get_key_lenght(string);
	trim = malloc((key_lenght + 1) * sizeof(char *));
	ft_strlcpy(trim, string, key_lenght + 1);
	while (temp != NULL)
	{
		if ((ft_strncmp(trim, temp->key, ft_strlen(temp->key)) == 0))
		{
			free (trim);
			return (temp);
		}
		temp = temp->next;
	}
	free(trim);
	return (temp);
}

void	refill_node(t_envp *node, char *string)
{
	free(node->content);
	free(node->key);
	if (node->output)
		free(node->output);
	node->content = ft_strdup(string);
	key_output(string, &node);
}

void	export(t_envp *env_list, t_node *command_table, t_vars *vars)
{
	t_envp	*temp;
	t_envp	*temp2;

	temp2 = get_node(env_list, command_table->command[1]);
	if (temp2)
		refill_node(temp2, command_table->command[1]);
	else
	{
		lstadd_back_envp(&env_list, command_table->command[1]);
		temp = lstlast_envp(env_list);
		key_output(command_table->command[1], &temp);
	}
	envp_to_array(env_list, vars);
	export_array(vars, env_list);
}
