/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/10 18:10:47 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	echo_n(t_node *command_table, int i)
{
	char	*str_to_print;

	while (command_table->command[i] != '\0')
	{
		if (ft_strncmp(command_table->command[i], "<<", 2) == 0)
			ft_putstr_fd("", 1);
		i++;
	}
	if (ft_strncmp(command_table->heredoc, "active", 6) == 0)
	{
		str_to_print = ft_substr(command_table->words, 7, \
		(ft_strlen(command_table->words) - 14));
	}
	else
		str_to_print = ft_substr(command_table->words, 7, \
		ft_strlen(command_table->words));
	ft_putstr_fd(str_to_print, 1);
	free(str_to_print);
	return (1);
}

static void	open_files(t_node *command_table)
{
	if (g_vars.append_open == 1)
		g_vars.f2 = open(g_vars.string_outfile, O_RDWR | O_APPEND);
	else
		g_vars.f2 = open(g_vars.string_outfile, \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (g_vars.f2 < 0)
		perror(g_vars.string_outfile);
}

static int	echo_with_outfile(t_node *command_table)
{
	char	*str_to_print;

	g_vars.string_outfile = q_find_token_outfile(command_table);
	if (g_vars.no_outfile == 0)
	{
		open_files(command_table);
		if (ft_strncmp(command_table->heredoc, "active", 6) == 0)
		{
			str_to_print = ft_substr(command_table->words, 5, \
			(ft_strlen(command_table->words) - 12));
		}
		else
			str_to_print = ft_substr(command_table->words, 5, \
			ft_strlen(command_table->words));
		ft_putstr_fd(str_to_print, g_vars.f2);
		ft_putchar_fd('\n', g_vars.f2);
		free(str_to_print);
		close(g_vars.f2);
		return (1);
	}
	return (0);
}

static int	echo_print(t_node *command_table, int i, \
							char *str_to_print)
{
	while (command_table->command[i] != '\0')
	{
		if (ft_strncmp(command_table->command[i], "<<", 2) == 0)
			ft_putstr_fd("", 1);
		i++;
	}
	if (echo_with_outfile(command_table) == 1)
		return (1);
	else
	{
		if (ft_strncmp(command_table->heredoc, "active", 6) == 0)
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

int	echo(t_node *command_table)
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
		return (echo_print(command_table, 1, str_to_print));
	return (1);
}
