/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/17 18:41:33 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	get_pos(t_envp *env_list, t_node *command_table)
{
	int	i;

	i = 0;
	while (env_list)
	{
		if ((ft_strncmp(env_list->key, command_table->command[1], \
			ft_strlen(command_table->command[1])) == 0) && \
			ft_strlen(command_table->command[1]) == ft_strlen(env_list->key))
			return (i);
		env_list = env_list->next;
		i++;
	}
	return (i);
}

static	void	unset_utils( t_envp *temp, t_envp *del, int position, int i)
{
	if (position == 0)
	{
		del = temp;
		temp = temp->next;
		del->next = NULL;
		free(del->content);
		free(del->output);
		free(del->key);
		free(del);
	}
	else
	{
		while (i < position - 1)
		{
			temp = temp->next;
			i++;
		}
		del = temp->next;
		temp->next = temp->next->next;
		del->next = NULL;
		free(del->content);
		free(del->output);
		free(del->key);
		free(del);
	}
}

static	int	find_key(t_envp *env_list, t_node *command_table)
{
	int	i;

	i = 0;
	while (env_list)
	{
		if ((ft_strncmp(env_list->key, command_table->command[1], \
			ft_strlen(command_table->command[1])) == 0) && \
			ft_strlen(command_table->command[1]) == ft_strlen(env_list->key))
			return (1);
		env_list = env_list->next;
		i++;
	}
	return (0);
}

void	unset(t_envp *env_list, t_node *command_table, t_vars *vars)
{
	t_envp	*temp;
	t_envp	*del;
	int		position;

	temp = env_list;
	if (find_key(env_list, command_table) == 1)
	{
		position = get_pos(env_list, command_table);
		unset_utils(temp, del, position, 0);
		free(vars->enviroment);
		envp_to_array(env_list, vars);
		print_envp(env_list);
	}
}
