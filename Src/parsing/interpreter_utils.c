/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interpreter_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/15 12:32:33 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/19 15:09:24 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_first_char(char *split, int i, t_node **temp)
{
	char	*tempo;

	tempo = ft_itoa(g_exitcode);
	if ((ft_isdigit(split[i]) == 1))
		i++;
	else if (split[i] == '?')
	{
		i++;
		add_to_word(temp, tempo);
	}
	free(tempo);
	return (i);
}

int	find_var(t_node **temp, int i, char *split, t_envp *env)
{
	char	*var;
	int		start;

	i = var_first_char(split, i, temp);
	if ((ft_isdigit(split[i - 1]) != 1) && split[i - 1] != '?')
	{
		start = i;
		while (split[i] != ' ')
		{
			i++;
			if (split[i] == 34 || split[i] == '.' || split[i] == '$' || \
				split[i] == '\0' || split[i] == 39)
				break ;
		}
		var = ft_substr(split, start, (i - start));
		var = env_var(env, var);
		add_to_word(temp, var);
	}
	if (split[i] == '$')
	{
		i++;
		i = find_var(temp, i, split, env);
	}
	return (i);
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
			(*temp)->outfile = ft_strdup(outfile);
			free(outfile);
			return (i);
		}
		i++;
	}
	end = i;
	outfile = ft_substr(split, start, (end - start));
	(*temp)->outfile = ft_strdup(outfile);
	free(outfile);
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
			(*temp)->infile = ft_strdup(infile);
			free(infile);
			return (i);
		}
		i++;
	}
	end = i;
	infile = ft_substr(split, start, (end - start));
	(*temp)->infile = ft_strdup(infile);
	free(infile);
	return (i);
}
