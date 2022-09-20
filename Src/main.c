/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/20 16:21:34 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell(void)
{
	char	*username;

	username = getenv("USER");
	printf("\033[H\033[J");
	printf("\n******************"
		"************************");
	printf("\n\n\t****ROLF AND QUILFORT'S SHELL****");
	printf("\n\n\t----USE AT YOUR OWN RISK----");
	printf("\n\n*******************"
		"***********************");
	printf("\n\nUSER is: @%s", username);
	printf("\n");
	sleep(2);
	printf("\033[H\033[J");
}

void	main_loop(int flag, t_envp *env, t_vars *vars)
{
	char			*input;
	char			**split;

	while (flag != EOF)
	{
		signals();
		input = readline("Minishell QR1.0: ");
		if (input == NULL)
		{
			flag = EOF;
			write(2, "exit", 4);
		}
		else
		{
			add_history(input);
			split = ft_split(input, '|');
			if (split[0] != NULL)
				command_table(split, env, vars);
		}
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_envp	*env;
	t_vars	*vars;

	// init_shell();
	vars = (t_vars *)malloc(sizeof(t_vars));
	if (vars == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	env = put_envp_in_list(envp, vars);
	// print_envp(env);
	envp_to_array(env, vars);
	main_loop(0, env, vars);
	return (0);
}

// QUILFORT'S TEST TO BRANCHE