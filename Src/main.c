/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/08/29 18:00:17 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_shell()
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

static void sigint_handler(int sig)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	// rl_replace_line("", 0);
	rl_on_new_line();
	// write(STDERR_FILENO, "\nMinishell QR1.0: ", 19);
	// write(1, "\nMinishell QR1.0: ", 19);
}

static void sigquit_handler(int sig)
{
	ioctl(STDIN_FILENO, TIOCSTI, "");
	sleep(0);
}

static void signals()
{
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
        perror("error");
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
        perror("error");
}

int	main(int argc, char *argv[], char **envp)
{
	char			*input;
	char			**split;
	int				flag;

	flag = 0;
	init_shell();
	while (flag != EOF)
	{
		signals();
		input = readline("Minishell QR1.0: ");
		if (input == NULL)
		{
			flag = EOF;
			write(1 ,"exit", 4);
		}
		else
		{
			add_history(input);
			split = ft_split(input, '|');
			if (split[0] != NULL)
				command_table(split, envp);
		}
	}
	return (0);
}

// QUILFORT'S TEST TO BRANCHE