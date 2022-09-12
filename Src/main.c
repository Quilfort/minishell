/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/12 17:28:45 by qfrederi      ########   odam.nl         */
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

void sigint_handler(int sig)
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
	// printf("it's signals time\n");
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
        perror("error");
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
        perror("error");
	// if (signal(SIGTRAP, sigint_handler) == SIG_ERR)
    //     perror("error");

}

void	main_loop(int flag, char **envp, t_envp *env)
{
	char			*input;
	char			**split;

	// printf("It's main time\n");
	while (flag != EOF)
	{
		signals();
		// printf("It's Loop time\n");
		input = readline("Minishell QR1.0: ");
		// printf("\n%s\n", input);
		if (input == NULL)
		{
			flag = EOF;
			write(2 ,"exit", 4);
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

static void	print_envp(t_envp *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("\ncontent %d:  ", i);
		printf("%s", list->content);
		printf("\nkey %d:  ", i);
		printf("%s", list->key);
		printf("\noutput %d:  ", i);
		printf("%s\n", list->output);
		list = list->next;
		i++;
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