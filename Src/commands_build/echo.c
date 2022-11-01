/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/01 16:58:42 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	echo_n(t_node *command_table)
{
	char	*str_to_print;

	if (command_table->heredoc != NULL)
	{
		str_to_print = ft_substr(command_table->words, 7, \
		(ft_strlen(command_table->words) - 14));
	}
	else
		str_to_print = ft_substr(command_table->words, 8, \
		ft_strlen(command_table->words));
	ft_putstr_fd(str_to_print, 1);
	free(str_to_print);
	return (1);
}

static void	open_files(t_vars *vars)
{
	if (vars->append_open == 1)
		vars->f2 = open(vars->string_outfile, O_RDWR | O_APPEND);
	else
		vars->f2 = open(vars->string_outfile, \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars->f2 < 0)
		perror(vars->string_outfile);
}

static int	echo_with_outfile(t_node *command_table, t_vars *vars)
{
	char	*str_to_print;

	vars->string_outfile = q_find_token_outfile(command_table, vars);
	if (vars->no_outfile == 0)
	{
		open_files(vars);
		if (command_table->heredoc != NULL)
		{
			str_to_print = ft_substr(command_table->words, 5, \
			(ft_strlen(command_table->words) - 12));
		}
		else
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

static int	echo_print(t_node *command_table, char *str_to_print, t_vars *vars)
{
	if (echo_with_outfile(command_table, vars) == 1)
		return (1);
	else
	{
		if (command_table->heredoc != NULL)
		{
			str_to_print = ft_substr(command_table->words, 5, \
			(ft_strlen(command_table->words) - 12));
		}
		else
			str_to_print = ft_substr(command_table->words, 5, \
			ft_strlen(command_table->words));
		ft_putendl_fd(str_to_print, 1);
		free(str_to_print);
		return (1);
	}
}

int	echo(t_node *command_table, t_vars *vars, t_envp *env_list)
{
	char	*str_to_print;
	t_envp	*temp;

	str_to_print = NULL;
	if (!command_table->command[1])
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if (ft_strcmp("~", command_table->command[1]) == 0)
	{
		temp = get_node(env_list, "HOME");
		ft_putendl_fd(temp->output, 1);
		return (1);
	}
	else if (ft_strncmp("-n", command_table->command[1], 2) == 0)
		return (echo_n(command_table));
	else
		return (echo_print(command_table, str_to_print, vars));
	return (1);
}
