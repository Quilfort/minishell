/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/24 19:01:21 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	digits_only(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (ft_isdigit((int)string[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	exit_argument_check(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i])
	{
		if (i >= 2)
			return (0);
		i++;
	}
	return (1);
}

static void	exit_program_error(char **arguments)
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
		exit(255);
	}
}

void	exit_program(t_node *command_table)
{
	int	exitcode;

	if (command_table->command[1] == NULL)
		exit(0);
	exit_program_error(command_table->command);
	if (digits_only(command_table->command[1]) == 1)
	{
		exitcode = ft_atoi(command_table->command[1]);
		if (exitcode > 255)
			exitcode -= 256;
		exit(exitcode);
	}
}
