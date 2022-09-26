/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 16:22:48 by rharing       #+#    #+#                 */
/*   Updated: 2022/09/26 14:44:33 by qfrederi      ########   odam.nl         */
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

int	redirect_here_doc(t_node *temp, char *split, int i, t_envp *env)
{
	char	*word;

	if (split[i + 2] == '\0')
	{
		word = ft_substr(split, i, 2);
		list_quotes(&temp, word);
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
		list_quotes(&temp, word);
		i++;
	}
	else
		i = list_infile(&temp, i, split);
	return (i);
}

int	redirect_outfile(t_node *temp, char *split, int i)
{
	char	*word;

	if (split[i + 2] == '\0')
	{
		word = ft_substr(split, i, 2);
		list_quotes(&temp, word);
		i = i + 2;
	}
	else if (split[i] == '>' && split[i + 1] == '>')
	{
		printf("Moeten functie voor append nog regelen");
		i++;
		i = list_outfile(&temp, i, split);
	}
	else
		i = list_outfile(&temp, i, split);
	return (i);
}

char	split_pipe(char *split, t_node *temp, t_envp *env)
{
	int		i;

	i = 0;
	fill_in(temp);
	while (split[i] != '\0')
	{
		i = split_word(&temp, i, split, env);
		if (split[i] == 39)
			i = list_single_quote(&temp, i, split, env);
		else if (split[i] == 34)
		{
			i++;
			i = list_double_quote(&temp, i, split, env);
		}
		else if (split[i] == '<' && split[i + 1] == '<')
			i = redirect_here_doc(temp, split, i, env);
		else if (split[i] == '>')
			i = redirect_outfile(temp, split, i);
		else if (split[i] == '<')
			i = redirect_infile(temp, split, i);
	}
	return (0);
}
