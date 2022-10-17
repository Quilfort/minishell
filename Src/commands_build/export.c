/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/17 16:35:05 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_envp *env_list, t_node *command_table, t_vars *vars)
{
	t_envp	*temp;

	if (vars->enviroment != NULL)
		freesplit(vars->enviroment);
	lstadd_back_envp(&env_list, command_table->command[1]);
	envp_to_array(env_list, vars);
	temp = lstlast_envp(env_list);
	key_output(command_table->command[1], &temp);
}
