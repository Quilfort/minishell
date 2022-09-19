/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 13:54:02 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/19 18:27:55 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

void list_quotes(t_node **temp, char *word)
{
	(*temp)->words = ft_strjoin((*temp)->words, word);
}

int	find_quote(t_node **temp, int i, char *split, int start)
{
	char	*pipe_split;
	int		end;

	end = i;
	pipe_split = ft_substr(split, start, (end - start));
	list_quotes(temp, pipe_split);
	return (i);
}

int list_double_quote(t_node **temp, int i, char *split, t_envp *env)
{
	char	*var;
	int		start;

	start = i;
	while (split[i] != '\0')
	{
		if (split[i] == 34)
		{
			i = find_quote(temp, i, split, start);
			i++;
			return (i);
		}
		else if (split[i] == '$')
		{
			if (split[i + 1] == 34)
			{
				i++;
				i = find_quote(temp, i, split, start);
				i++;
				return (i);
			}
			else if (split[i + 1] != ' ')
			{
				if (split[i + 1] == '\0')
					sleep(0);
				else
				{
					i = find_quote(temp, i, split, start);
					i++;
					start = i;
					while (split[i] != ' ')
					{
						i++;
						if (split[i] == 34)
							break ;
					}
					var = ft_substr(split, start, (i - start));
					var = env_var(env, var);
					list_quotes(temp, var);
					start = i;
					if (split[i] == 34)
					{
						i++;
						return (i);
					}
				}
			}
		}
		i++;
	}
	i = find_quote(temp, i, split, start);
	return (i);
}

int list_single_quote(t_node **temp, int i, char *split, t_envp *env)
{
	int		start;

	start = i;
	while (split[i] != '\0')
	{
		if (split[i] == 39)
		{
			i = find_quote(temp, i, split, start);
			i++;
			return (i);
		}
		i++;
	}
	i = find_quote(temp, i, split, start);
	return (i);
}