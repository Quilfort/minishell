/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/08/01 13:06:19 by rharing       ########   odam.nl         */
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
		split = ft_split(input, ' ');
		lexer(split, envp);
	}
	return (0);
}

// QUILFORT'S TEST TO BRANCHE