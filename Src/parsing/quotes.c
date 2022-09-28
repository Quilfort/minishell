/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 13:54:02 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/28 14:48:44 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_quotes(t_node **temp, char *word)
{
	(*temp)->words = ft_strjoin((*temp)->words, word);
}

int	find_quote(t_node **temp, int i, char *split, int start)
{
	char	*pipe_split;
	int		end;

	end = i;
	pipe_split = ft_substr(split, start, (end - start));
	list_quotes(temp, pipe_split);
	return (i);
}

int	var_in_double_quotes(t_node **temp, int i, char *split, t_envp *env)
{
	i++;
	i = find_var(temp, i, split, env);
	if (split[i] == 34)
	{
		i++;
		return (i);
	}
	else
		return (i);
}

int	list_double_quote(t_node **temp, int i, char *split, t_envp *env)
{
	int		start;

	start = i;
	while (split[i] != '\0')
	{
		if (split[i] == 34)
		{
			i = find_quote(temp, i, split, start);
			i++;
			return (i);
		}
		else if (split[i] == '$' && (split[i + 1] != '\0' && split[i + 1] \
				!= 34 && split[i + 1] != ' '))
		{
			i = find_quote(temp, i, split, start);
			i = var_in_double_quotes(temp, i, split, env);
			if (split[i - 1] == 34)
				return (i);
			else
				start = i;
		}	
		i++;
	}
	i = find_quote(temp, i, split, start);
	return (i);
}

int	list_single_quote(t_node **temp, int i, char *split, t_envp *env)
{
	int		start;

	start = i;
	while (split[i] != '\0')
	{
		if (split[i] == 39)
		{
			i = find_quote(temp, i, split, start);
			i++;
			return (i);
		}
		i++;
	}
	i = find_quote(temp, i, split, start);
	return (i);
}
