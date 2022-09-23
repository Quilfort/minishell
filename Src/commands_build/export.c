/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/21 17:13:32 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    export(t_envp *env_list, t_node *command_table, t_vars *vars)
{
    t_envp  *temp;

    lstadd_back_envp(&env_list, command_table->command[1]);
    free(vars->enviroment);
    envp_to_array(env_list, vars);
    temp = lstlast_envp(env_list);
    key_output(command_table->command[1], &temp);
}
