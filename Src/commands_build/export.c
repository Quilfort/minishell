/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/08 17:27:24 by qfrederi      ########   odam.nl         */
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
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static void	export_add_back(t_envp *env_list, t_vars *vars)
{
	t_envp	*temp;

	lstadd_back_envp(&env_list, vars->command_export);
	temp = lstlast_envp(env_list);
	key_output(vars->command_export, &temp);
}

void	export(t_envp *env_list, t_node *command_table, t_vars *vars)
{
	t_envp	*temp2;
	int		i;

	i = 7;
	while (command_table->content[i] != '\0')
	{
		i = find_command(command_table->content, i, vars, env_list);
		temp2 = get_node(env_list, vars->command_export);
		if (temp2)
		{
			if (has_equal(vars->command_export) == 1)
				refill_node(temp2, vars->command_export);
		}
		else
			export_add_back(env_list, vars);
		free(vars->command_export);
		if (command_table->content[i] == '\0')
			break ;
		else
			i++;
	}
	envp_to_array(env_list, vars);
	export_array(vars, env_list);
	vars->command_export = NULL;
}
