/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 12:32:33 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/21 13:15:14 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_word(t_node **temp, char *word)
{
	int		i;
	char	**split;

	split = ft_split(word, ' ');
	i = 0;
	while (split[i] != NULL)
	{
		(*temp)->words = ft_strjoin((*temp)->words, split[i]);
		(*temp)->words = ft_strjoin((*temp)->words, " ");
		i++;
	}
}

int	list_outfile(t_node **temp, int i, char *split)
{
	char	*outfile;
	int		start;
	int		end;

	i++;
	while (split[i] == ' ')
		i++;
	start = i;
	while (split[i] != '\0')
	{
		if (split[i] == ' ')
		{
			end = i;
			outfile = ft_substr(split, start, (end - start));
			(*temp)->outfile = ft_strjoin((*temp)->outfile, outfile);
			return (i);
		}
		i++;
	}
	end = i;
	outfile = ft_substr(split, start, (end - start));
	(*temp)->outfile = ft_strjoin((*temp)->infile, outfile);
	return (i);
}

int	list_infile(t_node **temp, int i, char *split)
{
	char	*infile;
	int		start;
	int		end;

	i++;
	while (split[i] == ' ')
		i++;
	start = i;
	while (split[i] != '\0')
	{
		if (split[i] == ' ')
		{
			end = i;
			infile = ft_substr(split, start, (end - start));
			(*temp)->infile = ft_strjoin((*temp)->infile, infile);
			return (i);
		}
		i++;
	}
	end = i;
	infile = ft_substr(split, start, (end - start));
	(*temp)->infile = ft_strjoin((*temp)->infile, infile);
	return (i);
}
