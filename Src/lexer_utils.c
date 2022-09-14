/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 12:32:33 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/14 13:52:33 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

void list_word(t_node **temp, char *word)
{
	(*temp)->words = ft_strjoin((*temp)->words, word);
	(*temp)->words = ft_strjoin((*temp)->words, " ");
}

int	list_outfile(t_node **temp, char **outfile, int i)
{
	i++;
	(*temp)->outfile = ft_strjoin((*temp)->outfile, outfile[i]);
	return (i);
}

int	list_infile(t_node **temp, char **infile, int i)
{
	i++;
	(*temp)->infile = ft_strjoin((*temp)->infile, infile[i]);
	return (i);
}

int list_single_quote(t_node **temp, char **pipe_split, int i)
{
	if (pipe_split[i + 1] != NULL)
	{
		list_word(temp, pipe_split[i]);
		i++;

		while (pipe_split[i][0] != 39)
		{
			if (pipe_split[i + 1] == NULL)
				break;
			list_word(temp, pipe_split[i]);
			i++;
		}
		list_word(temp, pipe_split[i]);
	}
	else
		list_word(temp, pipe_split[i]);
	return (i);	
}

// check is there is an " at the end. Case echo "$PWD" | var is PWD"


int list_double_quote(t_node **temp, char **pipe_split, int i, t_envp *env)
{
	char	*var;
	
	if (pipe_split[i][1] == '$')
	{
		var = ft_substr(pipe_split[i], 2 , ft_strlen(pipe_split[i]));
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
				break;
			else if (pipe_split[i][0] == '$')
			{
				var = ft_substr(pipe_split[i], 1 , ft_strlen(pipe_split[i]));
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