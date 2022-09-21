/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_command_table.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 15:13:19 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/21 17:29:13 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_init(t_node *command_table)
{
	command_table->command = ft_split(command_table->words, ' ');
	while (command_table->next != NULL)
	{
		command_table = command_table->next;
		command_table->command = ft_split(command_table->words, ' ');
	}
}

t_node	*create_command_table_list(char **split, t_envp *env)
{
	t_node			*node;
	t_node			*temp;
	char			**command_split;
	int				i;

	node = create_head(split[0]);
	i = 1;
	while (split[i] != '\0')
	{
		lstadd_back(&node, split[i]);
		i++;
	}
	i = 0;
	temp = node;
	while (temp != NULL)
	{
		split_pipe(split[i], temp, env);
		temp = temp->next;
		i++;
	}
	return (node);
}

void	command_table(char **split, t_envp	*env, t_vars *vars)
{
	t_node			*node;

	node = create_command_table_list(split, env);
	exec_init(node);
	if ((ft_strncmp("exit", node->command[0], 4) == 0) \
					&& (node->command[1] == NULL))
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	q_pipex_start(node, vars);
}
