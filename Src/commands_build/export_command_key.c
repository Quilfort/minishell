/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_command_key.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 18:15:56 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/16 17:01:48 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_key_var(char *content, int i, t_vars *vars, t_envp *env_list)
{
	int	start;

	i++;
	start = i;
	i = find_key_var_export(i, content, vars, env_list);
	return (i);
}

int	export_key_no_var(char *content, int i, t_vars *vars)
{
	int	start;

	start = i;
	while (content[i] != '\0' && content[i] != '=' && content[i] != ' ')
			i++;
	if (content[i] == '\0' || content[i] == ' ')
	{
		vars->command_export = ft_substr(content, start, i - start);
		return (i);
	}
	vars->command_export = ft_substr(content, start, i - start);
	return (i);
}

int	has_space_num(char *string)
{
	int	i;

	i = 6;
	while (string[i] != '\0')
	{
		if (string[i] != ' ')
		{
			if (ft_isdigit(string[i]) == 1 || string[i] == '!')
				return (2);
		}
		else
			return (1);
		i++;
	}
	return (0);
}
