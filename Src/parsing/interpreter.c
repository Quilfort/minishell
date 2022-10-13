/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interpreter.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 16:22:48 by rharing       #+#    #+#                 */
/*   Updated: 2022/10/12 19:42:43 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_in(t_node *temp)
{
	temp->words = NULL;
	temp->infile = NULL;	
	temp->outfile = NULL;
	temp->heredoc = NULL;
}

int	redirect_here_doc(t_node *temp, char *split, int i, t_envp *env)
{
	char	*word;

	if (split[i + 2] == '\0')
	{
		word = ft_substr(split, i, 2);
		add_to_word(&temp, word);
		i = i + 2;
	}
	else
		i = list_heredoc(&temp, split, i, env);
	return (i);
}

int	redirect_infile(t_node *temp, char *split, int i)
{
	char	*word;

	if (split[i + 1] == '\0')
	{
		word = ft_substr(split, i, 1);
		add_to_word(&temp, word);
		i++;
	}
	else
		i = list_infile(&temp, i, split);
	return (i);
}

int	redirect_outfile(t_node *temp, char *split, int i, t_vars *vars)
{
	char	*word;

	vars->append_open = 0;
	if (split[i + 2] == '\0')
	{
		word = ft_substr(split, i, 2);
		add_to_word(&temp, word);
		i = i + 2;
	}
	else if (split[i] == '>' && split[i + 1] == '>')
	{
		vars->append_open = 1;
		i++;
		i = list_outfile(&temp, i, split);
	}
	else
		i = list_outfile(&temp, i, split);
	return (i);
}

void	split_pipe(char *split, t_node *temp, t_envp *env, t_vars *vars)
{
	int		i;

	i = 0;
	fill_in(temp);
	// printf("this is split[i] = %s\n\n", split);
	// printf("this is split[0] = %c\n\n", split[0]);
	while (split[i] != '\0')
	{
		i = split_word(&temp, i, split, env);
		// printf("Do you work\n\n");
		// printf("[i] = %d\n\n", i);
		// printf("dit is split: %s\n\n", split);
		// printf("this is split[i] = %c\n\n", split[i]);
		// printf("this is split[0] = %c\n\n", split[0]);
		// printf("this is split[1] = %c\n\n", split[1]);
		// printf("this is split[2] = %c\n\n", split[2]);
		if (split[i] == '\'')
		{
			i++;
			i = list_single_quote(&temp, i, split, env);
		}
		else if (split[i] == 34)
		{
			i++;
			i = list_double_quote(&temp, i, split, env);
		}
		else if (split[i] == '<' && split[i + 1] == '<')
			i = redirect_here_doc(temp, split, i, env);
		else if (split[i] == '>')
			i = redirect_outfile(temp, split, i, vars);
		else if (split[i] == '<')
			i = redirect_infile(temp, split, i);
	}
}
