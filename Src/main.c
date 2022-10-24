/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/24 19:00:05 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_vars(t_vars *vars)
{
	vars->f1 = 0;
	vars->f2 = 0;
	vars->no_infile = 0;
	vars->no_outfile = 0;
	vars->env_count = 0;
	vars->enviroment = NULL;
	vars->cmd = NULL;
	vars->path = NULL;
	vars->path_cmd = NULL;
	vars->my_path = NULL;
	vars->string_infile = NULL;
	vars->string_outfile = NULL;
	vars->com = 0;
	vars->com_count = 0;
	vars->append_open = 0;
	vars->export_env = NULL;
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
		// system("leaks minishell");
	}
}

t_vars2 g_vars2;

int	main(int argc, char *argv[], char **envp)
{
	t_envp	*env;
	t_vars	*vars;

	if (argc == 1 && argv[0] != NULL)
	{
		vars = (t_vars *)malloc(sizeof(t_vars));
		if (vars == NULL)
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		init_vars(vars);
		env = put_envp_in_list(envp);
		envp_to_array(env, vars);
		export_array(vars);
		signals();
		main_loop(0, env, vars);
	}
	return (0);
}
