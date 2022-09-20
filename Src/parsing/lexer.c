/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 15:13:19 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/20 17:29:36 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_print_command(t_node *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("\ncontent %d:  ", i);
		printf("%s", list->content);
		printf("\nwords %d:  ", i);
		printf("%s\n", list->words);
		printf("\ninfile %d:  ", i);
		printf("%s\n", list->infile);
		printf("\noutfile %d:  ", i);
		printf("%s\n", list->outfile);
		printf("\nheredoc %d:  ", i);
		printf("%s\n", list->heredoc);
		printf("\ncommand[0] %d:  ", i);
		printf("%s\n", list->command[0]);
		list = list->next;
		i++;
	}
}

static void	fill_in(t_node *temp)
{
	temp->words = ft_strdup("");
	temp->infile = ft_strdup("");
	temp->outfile = ft_strdup("");
	temp->heredoc = ft_strdup("");
}

// als split[0] een spatie is na een '' of "" moet er wel een spatie komen.

int find_word(t_node **temp, int i, char *split, int start)
{
	char	*pipe_split;
	int		end;

	end = i;
	pipe_split = ft_substr(split, start, (end - start));
	list_word(temp, pipe_split);
	return (i);
}

static int find_var_in_word(t_node **temp, int i, char *split, t_envp *env)
{
	char	*var;
	int		start;

	start = i;
	while (split[i] != ' ')
	{
		i++;
		if (split[i] == '\0')
			break ;
	}
	var = ft_substr(split, start, (i - start));
	var = env_var(env, var);
	list_quotes(temp, var);
	return (i);
}

static int split_word(t_node **temp, int i, char *split, t_envp *env)
{
	int		start;
	char	*space;

	start = i;
	if (start != 0 && split[i] == ' ')
	{
		space = ft_substr(split, start, 1);
		list_quotes(temp, space);
	}
	while (split[i] != '\0')
	{
		if (split[i] == 39 || split[i] == 34 || \
			split[i] == '<' || split[i] == '>')
		{
			i = find_word(temp, i, split, start);
			return (i);
		}
		if (split[i] == '$')
		{
			if (split[i + 1] == '\0')
				sleep(0);
			else
			{
				i = find_word(temp, i, split, start);
				i++;
				i = find_var_in_word(temp, i, split, env);
				start = i;
				if (split[i] == ' ')
				{
					space = ft_substr(split, i, 1);
					list_quotes(temp, space);
				}
			}
		}
		i++;
	}
	i = find_word(temp, i, split, start);
	return (i);
}

char	split_pipe(char *split, t_node *temp, t_envp *env)
{
	int		i;
	char	*word;

	i = 0;
	fill_in(temp);
	while (split[i] != '\0')
	{
		i = split_word(&temp, i, split, env);
		if (split[i] == 39)
		{
			i++;
			i = list_single_quote(&temp, i, split, env);
		}
		else if (split[i] == 34)
		{
			i++;
			i = list_double_quote(&temp, i, split, env);
		}
		else if (split[i] == '<' && split[i + 1] == '<' )
		{
			if (split[i + 2] == '\0')
			{
				word = ft_substr(split, i, 2);
				list_quotes(&temp, word);
				i = i + 2;
			}
			else
				i = list_heredoc(&temp, split, i, env);
		}
		else if (split[i] == '>' && split[i + 1] == '>' )
		{
			if (split[i + 2] == '\0')
			{
				word = ft_substr(split, i, 2);
				list_quotes(&temp, word);
				i = i + 2;
			}
			else
			{
				printf("Moeten functie voor append nog regelen");
				i = i + 2;
			}
		}
		else if (split[i] == '<')
		{
			if (split[i + 1] == '\0')
			{
				word = ft_substr(split, i, 1);
				list_quotes(&temp, word);
				i++;
			}
			else
			{
				i++;
				i = list_infile(&temp, i, split);
			}
		}
		else if (split[i] == '>')
		{
			i++;
			i = list_outfile(&temp, i, split);
		}
	}
	return (0);
}

// static char	split_pipe(char *split, t_node *temp, t_envp *env)
// {
// 	char	**pipe_split;
// 	int		i;

// 	i = 0;
// 	pipe_split = ft_split(split, ' ');
// 	fill_in(temp);
// 	while (pipe_split[i] != NULL)
// 	{
// 		if (pipe_split[i][0] == 39)
// 			i = list_single_quote(&temp, pipe_split, i, env);
// 		else if (pipe_split[i][0] == 34)
// 			i = list_double_quote(&temp, pipe_split, i, env);
// 		else if (pipe_split[i][0] == '<' && pipe_split[i][1] == '<')
// 			i = list_heredoc(&temp, pipe_split, i, env);
// 		else if (pipe_split[i][0] == '<' && pipe_split[i][1] == '\0')
// 			i = list_infile(&temp, pipe_split, i);
// 		else if (pipe_split[i][0] == '>' && pipe_split[i][1] == '\0')
// 			i = list_outfile(&temp, pipe_split, i);
// 		else
// 			list_word(&temp, pipe_split[i]);
// 		i++;
// 	}
// 	return (0);
// }
