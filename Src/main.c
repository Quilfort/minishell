/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/14 11:53:04 by qfrederi      ########   odam.nl         */
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

void	main_loop(int flag, char **envp, t_envp *env)
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
				command_table(split, envp, env);
		}
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_envp	*env;
	t_envp	*temp;
	int		i;

	// init_shell();
	env = create_list_envp(envp[0]);
	i = 1;
	while (envp[i] != '\0')
	{
		lstadd_back_envp(&env, envp[i], 0);
		i++;
	}
	i = 0;
	temp = env;
	while (temp != NULL)
	{
		key_output(envp[i], &temp);
		temp = temp->next;
		i++;
	}
	// print_envp(env);
	main_loop(0, envp, env);
	return (0);
}

// QUILFORT'S TEST TO BRANCHE