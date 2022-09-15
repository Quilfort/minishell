/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   double_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 14:37:13 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/15 14:37:35 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

 // check is there is an " at the end. Case echo "$PWD" | var is PWD"

int list_double_quote(t_node **temp, char **pipe_split, int i, t_envp *env)
{
	char	*var;

	if (pipe_split[i][1] == '$')
	{
		var = ft_substr(pipe_split[i], 2, ft_strlen(pipe_split[i]));
		var = env_var(env, var);
		list_word(temp, var);
	}
	else if (pipe_split[i + 1] != NULL)
	{
		list_word(temp, pipe_split[i]);
		i++;
		while (pipe_split[i][0] != 34)
		{
			if (pipe_split[i + 1] == NULL)
				break ;
			else if (pipe_split[i][0] == '$')
			{
				var = ft_substr(pipe_split[i], 1, ft_strlen(pipe_split[i]));
				var = env_var(env, var);
				list_word(temp, var);
			}
			else
				list_word(temp, pipe_split[i]);	
			i++;
		}
		list_word(temp, pipe_split[i]);
	}
	else
		list_word(temp, pipe_split[i]);
	return (i);
}
