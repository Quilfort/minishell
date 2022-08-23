/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 12:32:33 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/08/23 14:06:05 by qfrederi      ########   odam.nl         */
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
	(*temp)->outfile = ft_strjoin((*temp)->outfile, outfile[i]);
	i++;
	(*temp)->outfile= ft_strjoin((*temp)->outfile, " ");
	(*temp)->outfile = ft_strjoin((*temp)->outfile, outfile[i]);
	return (i);
}

int	list_infile(t_node **temp, char **infile, int i)
{
	(*temp)->infile = ft_strjoin((*temp)->infile, infile[i]);
	i++;
	(*temp)->infile= ft_strjoin((*temp)->infile, " ");
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

int list_double_quote(t_node **temp, char **pipe_split, int i)
{
	if (pipe_split[i][1] == '$')
		printf("Function for env var");
	if (pipe_split[i + 1] != NULL)
	{
		list_word(temp, pipe_split[i]);
		i++;

		while (pipe_split[i][0] != 34)
		{
			if (pipe_split[i + 1] == NULL)
				break;
			if (pipe_split[i][0] == '$')
				printf("Function for env var");
			list_word(temp, pipe_split[i]);
			i++;
		}
		list_word(temp, pipe_split[i]);
	}
	else
		list_word(temp, pipe_split[i]);
	return (i);		
}