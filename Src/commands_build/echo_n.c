/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_n.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/08 13:33:31 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char c)
{
	return (c == 'n' || c == '-' || c == ' ');
}

static int	pos_check(int k, int p, char *string)
{
	if (k == 5 && p == 0)
		return (ft_strlen(string));
	if (k == 5 && p == 1)
		return (5);
	return (k);
}

static int	str_check(char *string)
{
	int	i;
	int	k;
	int	p;

	p = 0;
	i = 5;
	k = i;
	while (string[i])
	{
		if (!is_space(string[i]))
		{
			p = 1;
			break ;
		}
		while (string[i] == ' ')
		{
			i++;
			k = i;
		}
		i++;
	}
	k = pos_check(k, p, string);
	return (k);
}

int	echo_n(t_node *command_table)
{
	char	*str_to_print;
	int		start;

	start = str_check(command_table->words);
	if (start == 5 && command_table->command[2] == NULL)
	{
		ft_putendl_fd(command_table->command[1], 1);
		return (1);
	}
	if (command_table->heredoc != NULL)
	{
		str_to_print = ft_substr(command_table->words, 7, \
		(ft_strlen(command_table->words) - 14));
	}
	else
		str_to_print = ft_substr(command_table->words, start, \
		ft_strlen(command_table->words));
	ft_putstr_fd(str_to_print, 1);
	free(str_to_print);
	return (1);
}
