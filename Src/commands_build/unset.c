/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/03 12:08:22 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	get_pos(t_envp *env_list, t_node *command_table)
{
	int	i;

	i = 0;
	while (ft_strncmp(env_list->key, command_table->command[1], \
			ft_strlen(command_table->command[1])) != 0)
	{
		env_list = env_list->next;
		i++;
	}
	return (i);
}

static	void	unset_utils(t_envp *env_list, t_envp *temp, \
							t_envp *del, int position)
{
	int	i;

	i = 0;
	if (position == 0)
	{
		env_list = env_list->next;
		temp->next = NULL;
		free(temp);
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
		free(del);
	}
}

void	unset(t_envp *env_list, t_node *command_table, t_vars *vars)
{
	t_envp	*temp;
	t_envp	*del;
	int		position;

	temp = env_list;
	position = get_pos(env_list, command_table);
	unset_utils(env_list, temp, del, position);
	free(vars->enviroment);
	envp_to_array(env_list, vars);
}
