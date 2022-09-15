/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 12:32:33 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/15 17:09:17 by qfrederi      ########   odam.nl         */
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
