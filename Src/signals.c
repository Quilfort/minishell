/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 17:33:32 by rharing       #+#    #+#                 */
/*   Updated: 2022/09/15 19:20:49 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
			pexit("sigint", EXIT_FAILURE);
		rl_on_new_line();
		// write(STDERR_FILENO, "WTF", 3);
	}
	if (sig == SIGQUIT)
	{
		if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
			pexit("sigquit", EXIT_FAILURE);
		// write(STDERR_FILENO, "jaa", 3);
		sleep(0);
	}
}

void	signals(void)
{
	struct sigaction	act;

	act.sa_handler = &sig_handler;
	if (sigaction(SIGINT, &act, NULL) == -1)
		pexit("sigaction", EXIT_FAILURE);
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		pexit("sigaction", EXIT_FAILURE);

}