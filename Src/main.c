/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/13 17:46:45 by rharing       ########   odam.nl         */
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

char	*rl_history(void)
{
	static char	*input;

	if (input)
	{
		free (input);
		input = (char *) NULL;
	}
	input = readline("Minishell QR1.0: ");
	if (input != NULL)
		input[ft_strlen(input) + 1] = '\0';
	if (input && *input)
		add_history (input);
	return (input);
}

void	main_loop(int flag, t_envp *env, t_vars	*vars)
{
	char			*input;

	while (flag != EOF)
	{
		input = rl_history();
		if (input == NULL)
		{
			flag = EOF;
			write(2, "exit", 4);
		}
		else if (input != NULL)
			command_table(input, env, vars);
	}
}

int	g_exitcode;

int	main(int argc, char *argv[], char **envp)
{
	t_envp	*env;
	t_vars	*vars;

	vars = (t_vars *)malloc(sizeof(t_vars));
	if (vars == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	env = put_envp_in_list(envp);
	envp_to_array(env, vars);
	signals();
	// init_shell();
	main_loop(0, env, vars);
	return (0);
}
