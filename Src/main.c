/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/08/11 14:55:48 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	char			*input;
	char			**split;

	while (1)
	{
		input = readline("Minishell QR1.0: ");
		add_history(input);

		split = ft_split(input, '|');
		if (split[0] != NULL)
			command_table(split, envp);

	}
	return (0);
}

// QUILFORT'S TEST TO BRANCHE