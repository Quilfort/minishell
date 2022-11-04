/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/04 14:23:16 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*get_node(t_envp *env_list, char *string)
{
	t_envp	*temp;

	temp = env_list;
	while (temp != NULL)
	{
		if ((ft_strncmp(string, temp->key, ft_strlen(temp->key)) == 0))
			return (temp);
		temp = temp->next;
	}
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

int	has_equal(char *string)
{
	int i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	export(t_envp *env_list, t_node *command_table, t_vars *vars)
{
	t_envp	*temp;
	t_envp	*temp2;
	int		i;

	i = 1;
	while (command_table->command[i] != NULL)
	{
		temp2 = get_node(env_list, command_table->command[i]);
		if (temp2)
		{
			if (has_equal(command_table->command[i]) == 1)
				refill_node(temp2, command_table->command[i]);
		}
		else
		{
			lstadd_back_envp(&env_list, command_table->command[i]);
			temp = lstlast_envp(env_list);
			key_output(command_table->command[i], &temp);
		}
		i++;
	}
	envp_to_array(env_list, vars);
	export_array(vars, env_list);
}
