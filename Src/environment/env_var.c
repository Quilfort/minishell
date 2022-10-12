/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:43:32 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/12 15:36:21 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_var(t_envp *list, char *var)
{
	char	*var_string;
	char	*output;

	var_string = var;
	while ((ft_strncmp(var_string, list->key, ft_strlen(list->key)) != 0) && \
			list->next != NULL)
	{
		list = list->next;
	}
	if (ft_strncmp(var_string, list->key, ft_strlen(list->key)) == 0 && \
		(ft_strlen(var_string) == ft_strlen(list->key)))
	{
		output = list->output;
		free(var_string);
		return (output);
	}	
	else
	{
		free(var_string);
		return ("");
	}
}

void	key_output(char *split, t_envp **temp)
{
	int		i;
	int		start;
	char	*key;
	char	*output;

	i = 0;
	(*temp)->key = ft_strdup("");
	(*temp)->output = ft_strdup("");
	if (split != NULL)
	{
		while (split[i] != '=')
			i++;
		key = ft_substr(split, 0, i);
		(*temp)->key = ft_strjoin((*temp)->key, key);
		i++;
		start = i;
		while (split[i] != '\0')
			i++;
		output = ft_substr(split, start, (i - start));
		(*temp)->output = ft_strjoin((*temp)->output, output);
	}
}
