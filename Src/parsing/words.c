/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   words.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 12:34:26 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/13 16:13:26 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_space(t_node **temp, char *split, int start)
{
	char	*space;

	if (start != 0 && split[start] == ' ')
	{
		space = " ";
		add_to_word(temp, space);
	}
}

char	*ft_strjoin1(char *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	size_t	i;
	char	*pointer;

	i = 0;
	s1len = ft_strlen (s1);
	s2len = ft_strlen (s2);
	pointer = malloc (s1len + s2len + 1);
	if (pointer == NULL)
		return (pointer);
	while (s1[i] != '\0')
	{
		pointer[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{	
		pointer[s1len + i] = s2[i];
		i++;
	}
	pointer[s1len + s2len] = '\0';
	free(s1);
	return (pointer);
}


void	freesplit(char **split)
{
	int i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

// add split to one string. strdup to words. free the string
void	add_to_word_split(t_node **temp, char *word, int space)
{
	int		i;
	char	**split;
	char	*joined;
	char	*memory;

	split = ft_split(word, ' ');
	i = 0;
	// printf("This is word = %s\n\n", word);

	while (split[i] != NULL)
	{
		if ((*temp)->words == NULL)
			(*temp)->words = ft_strdup(split[i]);
		else
			(*temp)->words = ft_strjoin1((*temp)->words, split[i]);
		if (split[i + 1] != NULL)
			(*temp)->words = ft_strjoin1((*temp)->words, " ");
		else
		{
			if (space == 1)
				(*temp)->words = ft_strjoin1((*temp)->words, " ");
		}
		i++;
	}

	// while (split[i] != NULL)
	// {
	// 	if ((*temp)->words == NULL)
	// 	{
	// 		memory = ft_strdup(split[i]);
	// 		(*temp)->words = memory;
	// 		free(memory);
	// 	}
	// 	else
	// 	{
	// 		memory = ft_strjoin((*temp)->words, split[i]);
	// 		(*temp)->words = memory;
	// 		free(memory);
	// 	}
	// 	if (split[i + 1] != NULL)
	// 	{
	// 		memory = ft_strjoin((*temp)->words, " ");
	// 		(*temp)->words = memory;
	// 		free(memory);
	// 	}
	// 	else
	// 	{
	// 		if (space == 1)
	// 		{
	// 			memory = ft_strjoin((*temp)->words, " ");
	// 			(*temp)->words = memory;
	// 			free(memory);
	// 		}
	// 	}
	// 	i++;
	// }

	// while (split[i] != NULL)
	// {
	// 	if ((*temp)->words == NULL)
	// 	{
	// 		memory = ft_strdup(split[i]);
	// 		(*temp)->words = ft_strdup(memory);
	// 		free(memory);
	// 	}
	// 	else
	// 	{
	// 		memory = ft_strdup(split[i]);
	// 		(*temp)->words = ft_strjoin((*temp)->words, memory);
	// 		free(memory);
	// 	}
	// 	if (split[i + 1] != NULL)
	// 		(*temp)->words = ft_strjoin((*temp)->words, " ");
	// 	else
	// 	{
	// 		if (space == 1)
	// 			(*temp)->words = ft_strjoin((*temp)->words, " ");
	// 	}
	// 	i++;
	// }


	// while (split[i] != NULL)
	// {
	// 	if (i == 0)
	// 		joined = ft_strdup(split[i]);
	// 	else
	// 		joined = ft_strjoin(joined, split[i]);
	// 	printf("This is joined loop = %s\n\n", joined);
	// 	if (split[i + 1] != NULL)
	// 		joined = ft_strjoin(joined, " ");
	// 	else
	// 	{
	// 		if (space == 1)
	// 			joined = ft_strjoin(joined, " ");
	// 	}
	// 	i++;
	// }
	// printf("This is joined end = %s\n\n", joined);
	// if ((*temp)->words == NULL)
	// 	(*temp)->words = ft_strdup(joined);
	// else
	// 	(*temp)->words = ft_strjoin((*temp)->words, joined);
	// free(joined);
	freesplit(split);
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
	add_to_word_split(temp, pipe_split, space);
	free(pipe_split);
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
			i = find_word(temp, i, split, start);
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
