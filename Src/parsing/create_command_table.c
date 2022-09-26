/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_command_table.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 15:13:19 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/26 13:31:24 by qfrederi      ########   odam.nl         */
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

int	make_pipes(char *split, int i)
{
	while (split[i] != '|' && split[i] != '\0')
	{
		if (split[i] == 34)
		{
			i++;
			while (split[i] != '\0' && split[i] != 34)
				i++;
		}
		else if (split[i] == 39)
		{
			i++;
			while (split[i] != '\0' && split[i] != 39)
				i++;
		}
		i++;
	}
	return (i);
}

int	add_to_list(t_node *node, int i, char *split)
{
	char	*content;
	int		start;

	start = i;
	i = make_pipes(split, i);
	content = ft_substr(split, start, (i - start));
	lstadd_back(&node, content);
	i++;
	return (i);
}

t_node	*create_command_table_list(char *split, t_envp *env)
{
	t_node			*node;
	t_node			*temp;
	int				i;

	i = 0;
	i = make_pipes(split, i);
	node = create_head(ft_substr(split, 0, i));
	i++;
	while (split[i] != '\0')
	{
		i = add_to_list(node, i, split);
	}
	temp = node;
	while (temp != NULL)
	{
		split_pipe(temp->content, temp, env);
		temp = temp->next;
	}
	return (node);
}

int	jaweetikt(t_node *command_table, t_envp *env, t_vars *vars)
{
	if ((ft_strncmp("export", command_table->command[0], 6) == 0) \
							&& (command_table->command[1] != NULL))
	{
		export(env, command_table, vars);
		return (1);
	}
	if ((ft_strncmp("cd", command_table->command[0], 2) == 0))
	{
		open_folder(command_table);
		return (1);
	}
	if ((ft_strncmp("unset", command_table->command[0], 5) == 0) \
							&& (command_table->command[1] != NULL))
	{
		unset(env, command_table, vars);
		return (1);
	}
	return (0);
}

void	command_table(char *split, t_envp *env, t_vars *vars)
{
	t_node			*node;

	node = create_command_table_list(split, env);
	exec_init(node);
	if (node->command[0] == NULL)
		main_loop(0, env, vars);
	if ((ft_strncmp("exit", node->command[0], 4) == 0) \
					&& (node->command[1] == NULL))
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	// if (jaweetikt(node, env, vars) == 0)
	// 	q_pipex_start(node, vars);
	list_print_command(node);
}
