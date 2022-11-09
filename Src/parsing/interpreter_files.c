/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interpreter_files.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 13:37:38 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/09 13:44:54 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	list_outfile_een(t_node *temp, char *outfile)
{
	if (temp->outfile)
		free(temp->outfile);
	temp->outfile = ft_strdup(outfile);
	free(outfile);
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
			list_outfile_een((*temp), outfile);
			return (i);
		}
		i++;
	}
	end = i;
	outfile = ft_substr(split, start, (end - start));
	list_outfile_een((*temp), outfile);
	return (i);
}

static void	list_infile_een(t_node *temp, char *infile)
{
	if (temp->infile)
		free(temp->infile);
	temp->infile = ft_strdup(infile);
	free(infile);
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
			list_infile_een((*temp), infile);
			return (i);
		}
		i++;
	}
	end = i;
	infile = ft_substr(split, start, (end - start));
	list_infile_een((*temp), infile);
	return (i);
}
