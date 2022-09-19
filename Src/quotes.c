/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 14:37:13 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/15 19:18:08 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

static char *end_quote_output(char *pipe_split, t_envp *env, int flag)
{
	char	*var;
	int		var_len;

	var_len = ft_strlen(pipe_split);
	if (flag == 1)
	{
		if (pipe_split[var_len - 1] == 34)
			var = ft_substr(pipe_split, 1, (var_len - 2));
		else
			var = ft_substr(pipe_split, 1, (var_len - 1));
	}
	if (flag == 2)
	{
		if (pipe_split[var_len - 1] == 39)
			var = ft_substr(pipe_split, 1, (var_len - 2));
		else
			var = ft_substr(pipe_split, 1, (var_len - 1));
	}
	if (flag == 3)
	{
		if (pipe_split[var_len - 1] == 34)
			var = ft_substr(pipe_split, 0, (var_len - 1));
		else
			var = ft_substr(pipe_split, 0, (var_len));
	}
	if (flag == 4)
	{
		if (pipe_split[var_len - 1] == 39)
			var = ft_substr(pipe_split, 0, (var_len - 1));
		else
			var = ft_substr(pipe_split, 0, (var_len));
	}
	return (var);	

}

static char *quote_output(char *pipe_split, t_envp *env, int flag)
{
	char	*var;
	int		var_len;

	var_len = ft_strlen(pipe_split);
	if (flag == 0)
	{
		if (pipe_split[var_len - 1] == 34)
			var = ft_substr(pipe_split, 2, (var_len - 3));
		else
			var = ft_substr(pipe_split, 2, var_len);
	}
	if (flag == 1 || flag == 3)
		var = ft_substr(pipe_split, 1, var_len);	
	if (flag == 2)
	{
		if (pipe_split[var_len - 1] == 34)
			var = ft_substr(pipe_split, 1, (var_len - 2));
		else
			var = ft_substr(pipe_split, 1, (var_len - 1));
	}
	if (flag == 0 || flag == 2 || flag == 3)
		var = env_var(env, var);
	return (var);	
}

int list_single_quote(t_node **temp, char **pipe_split, int i, t_envp *env)
{
	char	*var;

	if (pipe_split[i + 1] != NULL)
	{
		var = quote_output(pipe_split[i], env, 1);
		list_word(temp, var);
		i++;
		while (pipe_split[i][0] != 39)
		{
			if (pipe_split[i + 1] == NULL)
				break ;
			list_word(temp, pipe_split[i]);
			i++;
		}
		if (pipe_split[i][0] == 39)
			return (i);
		else
		{
			var = end_quote_output(pipe_split[i], env, 4);
			list_word(temp, var);
		}
	}
	else
	{
		var = end_quote_output(pipe_split[i], env, 2);
		list_word(temp, var);
	}
	return (i);	
}

int list_double_quote(t_node **temp, char **pipe_split, int i, t_envp *env)
{
	char	*var;
	int		var_len;

	if (pipe_split[i][1] == '$')
	{
		var = quote_output(pipe_split[i], env, 0);
		list_word(temp, var);
	}
	else if (pipe_split[i + 1] != NULL)
	{
		var = quote_output(pipe_split[i], env, 1);
		list_word(temp, var);
		i++;
		while (pipe_split[i][0] != 34)
		{
			if (pipe_split[i + 1] == NULL)
				break ;
			else if (pipe_split[i][0] == '$')
			{
				var = quote_output(pipe_split[i], env, 3);
				list_word(temp, var);
			}
			else
				list_word(temp, pipe_split[i]);	
			i++;
		}
		if (pipe_split[i][0] == 34)
			return (i);
		else if (pipe_split[i][0] == '$')
		{

			var = quote_output(pipe_split[i], env, 2);
			list_word(temp, var);
		}
		else
		{
			var = end_quote_output(pipe_split[i], env, 3);
			list_word(temp, var);
		}
	}
	else
	{
		var = end_quote_output(pipe_split[i], env, 1);
		list_word(temp, var);
	}
	return (i);
}

// echo "heey $USER is $USER is $USER pwd"" $PWD "
// heey qfrederi is qfrederi is qfrederi pwd"" /Users/qfrederi/Desktop/minishell_github 
// echo "$PWD"$PWD"$PWD" - Even aantal " Dit werkt
// echo "$PWD"$PWD" - Oneven aantal " Dit werkt niet

// echo 1 "2" 3 4 "5"

// vanaf 2 spliten we
// 2"

// "3

// 4"

// "5"

// 2 iterate - werk magic

// 3

// // in functie met quotes ""
// split op ""

// " iteraten tot je een " tegenkomt
// tussendoor voor je bij " ook $ uit"
// ga je uit de functie.

// Daarna iterate je over het hele string over er nog een " aan komt. 
// Zo ja, dan ga je opnieuw met de hele string in doublequote functie
// Zo nee, dan split je verder zoals we het in onze functie doen.

