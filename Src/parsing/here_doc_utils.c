/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 13:25:38 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/19 13:29:31 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free_both(char *s1, char *s2)
{
	size_t	i;
	char	*join;

	i = 0;
	join = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (join == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{	
		join[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	join[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	free(s2);
	return (join);
}

char	*delimiter_without_quotes(char *delimiter)
{
	char	*output;
	int		start;
	int		i;

	i = 0;
	output = NULL;
	if (delimiter[0] != 39 && delimiter[0] != 34)
		start = i;
	else
	{
		i++;
		while (delimiter[i] == 39 && delimiter[i] == 34 && delimiter[i] != '\0')
			i++;
		start = i;
	}
	while (delimiter[i] != '\0')
	{
		if (delimiter[i] == 39 || delimiter[i] == 34)
		{
			if (output == NULL)
				output = ft_substr(delimiter, start, (i - start));
			else
			output = ft_strjoin_free_both(output, \
						(ft_substr(delimiter, start, (i - start))));
			start = i + 1;
		}
		i++;
	}
	if (output == NULL)
		output = ft_substr(delimiter, start, (i - start));
	else
		output = ft_strjoin_free_both(output, \
						(ft_substr(delimiter, start, (i - start))));
	free(delimiter);
	return (output);
}