/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   words.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 12:34:26 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/28 17:37:12 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_space(t_node **temp, char *split, int start)
{
	char	*space;

	if (start != 0 && split[start] == ' ')
	{
		space = ft_substr(split, start, 1);
		list_quotes(temp, space);
	}
}

void	list_word(t_node **temp, char *word, int space)
{
	int		i;
	char	**split;

	split = ft_split(word, ' ');
	i = 0;
	while (split[i] != NULL)
	{
		(*temp)->words = ft_strjoin((*temp)->words, split[i]);
		if (split[i + 1] != NULL)
				(*temp)->words = ft_strjoin((*temp)->words, " ");
		else
		{
			if (space == 1)
				(*temp)->words = ft_strjoin((*temp)->words, " ");
		}
		i++;
	}
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
