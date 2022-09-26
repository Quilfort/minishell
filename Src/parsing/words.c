/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   words.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 12:34:26 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/26 15:53:01 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_first_char(char *split, int i, t_node **temp)
{
	if ((ft_isdigit(split[i]) == 1))
		i++;
	else if (split[i] == '?')
	{
		i++;
		list_quotes(temp, "0");
	}
	return (i);
}

int	find_var(t_node **temp, int i, char *split, t_envp *env)
{
	char	*var;
	int		start;

	i = var_first_char(split, i, temp);
	if ((ft_isdigit(split[i - 1]) != 1) && split[i - 1] != '?')
	{
		start = i;
		while (split[i] != ' ')
		{
			i++;
			if (split[i] == 34 || split[i] == '.' || split[i] == '$' || \
				split[i] == '\0' || split[i] == 39)
				break ;
		}
		var = ft_substr(split, start, (i - start));
		var = env_var(env, var);
		list_quotes(temp, var);
	}
	if (split[i] == '$')
	{
		i++;
		i = find_var(temp, i, split, env);
	}
	return (i);
}

int	find_word(t_node **temp, int i, char *split, int start)
{
	char	*pipe_split;
	int		end;
	int		space;

	space = 0;
	end = i;
	pipe_split = ft_substr(split, start, (end - start));
	if (split[i - 1] == ' ')
		space = 1;
	list_word(temp, pipe_split, space);
	return (i);
}

static int	word_start_space(t_node **temp, char *split, int i)
{
	add_space(temp, split, i);
	return (i);
}

int	split_word(t_node **temp, int i, char *split, t_envp *env)
{
	int		start;

	start = word_start_space(temp, split, i);
	while (split[i] != '\0')
	{
		if (split[i] == 39 || split[i] == 34 || \
			split[i] == '<' || split[i] == '>')
		{
			i = find_word(temp, i, split, start);
			return (i);
		}
		if ((split[i] == '$' && (split[i + 1] != ' ' && split[i + 1] != '\0')))
		{
			i = find_quote(temp, i, split, start);
			i++;
			i = find_var(temp, i, split, env);
			if (split[i] == 39 || split[i] == 34)
				return (i);
			start = word_start_space(temp, split, i);
		}
		i++;
	}
	i = find_word(temp, i, split, start);
	return (i);
}
