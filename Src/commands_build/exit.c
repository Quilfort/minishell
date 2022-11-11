/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/11 12:40:35 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_program_error(char **arguments)
{
	if (digits_only(arguments[1]) == 0)
	{
		ft_putstr_fd("Minishell: exit: ", 1);
		ft_putstr_fd(arguments[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(255);
	}
	else if (exit_argument_check(arguments) == 0)
	{
		ft_putstr_fd("Minishell: exit: ", 1);
		ft_putstr_fd("too many arguments\n", 1);
		g_vars2.exitcode = 1;
		return (1);
	}
	return (0);
}

void	exit_program(t_node *command_table)
{
	int	exitcode;

	if (command_table->command[1] == NULL)
		exit(g_vars2.exitcode);
	exit_program_error(command_table->command);
	if (digits_only(command_table->command[1]) == 1)
	{
		exitcode = ft_atoi(command_table->command[1]);
		if (exitcode > 255)
			exitcode -= 256;
		exit(exitcode);
	}
}

static void	exit_with_one_digit(t_node *node, t_vars *vars, t_envp *env)
{
	int	exitcode;

	exitcode = ft_atoi(node->command[1]);
	if (exitcode > 255)
		exitcode -= 256;
	free(node);
	freesplit(vars->enviroment);
	freesplit(vars->export_env);
	free_env_list(env);
	exit(exitcode);
}

int	exit_now_questionmark(t_node *node, t_vars *vars, t_envp *env)
{
	if (node->command[0] != NULL)
	{
		if ((ft_strncmp("exit", node->command[0], 4) == 0) \
			&& ft_strlen("exit") == ft_strlen(node->command[0]) \
			&& node->next == NULL)
		{
			ft_putstr_fd("exit\n", 2);
			if (node->command[1] == NULL)
				exit(g_vars2.exitcode);
			if (exit_program_error(node->command) == 0)
			{
				if (digits_only(node->command[1]) == 1)
					exit_with_one_digit(node, vars, env);
			}
			else
				return (1);
		}
	}
	return (0);
}
