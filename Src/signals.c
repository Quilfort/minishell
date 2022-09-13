/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 17:33:32 by rharing       #+#    #+#                 */
/*   Updated: 2022/09/13 18:03:34 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int sig)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	// rl_replace_line("", 0);
	rl_on_new_line();
	// write(STDERR_FILENO, "\nMinishell QR1.0: ", 19);
	// write(1, "\nMinishell QR1.0: ", 19);
}

static void	sigquit_handler(int sig)
{
	ioctl(STDIN_FILENO, TIOCSTI, "");
	sleep(0);
}

void	signals(void)
{
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
		perror("error");
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		perror("error");
	// if (signal(SIGTRAP, sigint_handler) == SIG_ERR)
    //     perror("error");
}
