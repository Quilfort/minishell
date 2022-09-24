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

static	int	echo_n(t_node *command_table, int i)
{
	char	*string_to_print;

	while (command_table->command[i] != '\0')
	{
		if (ft_strncmp(command_table->command[i], "<<", 2) == 0)
			ft_putstr_fd("", 1);
		i++;
	}
	string_to_print = ft_substr(command_table->words, 7, \
							ft_strlen(command_table->words));
	ft_putstr_fd(string_to_print, 1);
	free(string_to_print);
	return (1);
}

static int	echo_with_outfile(t_node *command_table, t_vars *vars)
{
	char	*str_to_print;

	vars->string_outfile = q_find_token_outfile(command_table, vars);
	if (vars->no_outfile == 0)
	{
		vars->f2 = open(vars->string_outfile, \
						O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (vars->f2 < 0)
			perror(vars->string_outfile);
		str_to_print = ft_substr(command_table->words, 5, \
		ft_strlen(command_table->words));
		ft_putstr_fd(str_to_print, vars->f2);
		ft_putchar_fd('\n', vars->f2);
		free(str_to_print);
        close(vars->f2);
		return (1);
	}
	return (0);
}

static int echo_print(t_node *command_table, t_vars *vars, int i, char *str_to_print)
{
    while (command_table->command[i] != '\0')
    {
        if (ft_strncmp(command_table->command[i], "<<", 2) == 0)
            ft_putstr_fd("", 1);
        i++;
    }
    if (echo_with_outfile(command_table, vars) == 1)
        return (1);
    else
    {
        str_to_print = ft_substr(command_table->words, 5, \
        ft_strlen(command_table->words));
        ft_putstr_fd(str_to_print, 1);
        ft_putchar_fd('\n', 1);
        free(str_to_print);
        return(1);
    }
}

int	echo(t_node *command_table, t_vars *vars)
{
	int		i;
	char	*str_to_print;
	int		pid;

	i = 2;
	if (!command_table->command[1])
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if (ft_strncmp("-n", command_table->command[1], 2) == 0)
		return (echo_n(command_table, i));
	else
        return(echo_print(command_table, vars, 1, str_to_print));
	return (1);
}
