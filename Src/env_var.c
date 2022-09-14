/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:43:32 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/14 12:51:38 by qfrederi      ########   odam.nl         */
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

// char	env_var_envp(char **envp, char *var)
// {
// 	char	*var_string;
// 	char	*output;
// 	int		var_len;

// 	var_string = ft_strjoin(var, "=");
// 	var_len = ft_strlen(var_string);

// 	printf("dit is var_string = %s\n", var_string);
// 	printf("dit is var_string = %d\n", var_len);
// 	printf("dit is var = %s\n", var);

// 	while (ft_strncmp(var_string, *envp, var_len) && *(envp + 1))
// 		envp++;
// 	if (ft_strncmp(var_string, *envp, var_len) != 0)
// 		return (*var);
// 	output = ft_strtrim(*envp, var_string);
// 	printf("dit is output = %s\n", output);
// 	return (*output);
// }

char	*env_var(t_envp *list, char *var)
{
	char	*var_string;
	char	*output;
	int		var_len;

	var_string = var;
	var_len = ft_strlen(var_string);

	// printf("dit is var_string = %s\n", var_string);
	// printf("dit is var_string = %d\n", var_len);
	// printf("dit is var = %s\n", var);

	while ((ft_strncmp(var_string, list->key, var_len) != 0) && (var_len != ft_strlen(list->key)) && list->next != NULL)
	{
		list = list->next;
	}
	// if (ft_strncmp(var_string, list->key, var_len) != 0 && (var_len != ft_strlen(list->key)))
	// 	return (var);
	// else
	// {
	// 	output = list->output;
	// 	// printf("dit is output = %s\n", output);
	// 	return (output);
	// }
	if (ft_strncmp(var_string, list->key, var_len) == 0 && (var_len == ft_strlen(list->key)))
	{
		output = list->output;
		// printf("dit is output = %s\n", output);
		return (output);
	}
		
	else
	{
		return (var);
	}
}


void	key_output(char *split, t_envp **temp)
{
	int 	i;
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
