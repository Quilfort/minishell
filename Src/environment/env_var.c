/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:43:32 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/17 17:26:46 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// alleen nodig voor testen
void	print_envp(t_envp *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("\ncontent %d:  ", i);
		printf("%s", list->content);
		printf("\nkey %d:  ", i);
		printf("%s", list->key);
		printf("\noutput %d:  ", i);
		printf("%s\n", list->output);
		list = list->next;
		i++;
	}
}

char	*env_var(t_envp *list, char *var)
{
	char	*output;

	while ((ft_strncmp(var, list->key, ft_strlen(list->key)) != 0) && \
			list->next != NULL)
	{
		list = list->next;
	}
	if (ft_strncmp(var, list->key, ft_strlen(list->key)) == 0 && \
		(ft_strlen(var) == ft_strlen(list->key)))
	{
		output = list->output;
		free(var);
		return (output);
	}	
	else
	{
		free(var);
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
	if (split != NULL)
	{
		while (split[i] != '=')
			i++;
		key = ft_substr(split, 0, i);
		(*temp)->key = ft_strdup(key);
		free(key);
		i++;
		start = i;
		while (split[i] != '\0')
			i++;
		output = ft_substr(split, start, (i - start));
		(*temp)->output = ft_strdup(output);
		free(output);
	}
}
