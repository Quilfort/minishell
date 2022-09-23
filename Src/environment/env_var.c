/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:43:32 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/21 12:47:40 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (output);
	}	
	else
		return ("");
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
