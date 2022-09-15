/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 15:13:19 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/15 11:35:40 by qfrederi      ########   odam.nl         */
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

static char	split_pipe(char *split, t_node *temp, t_envp *env)
{
	char	**pipe_split;
	int		i;

	i = 0;
	pipe_split = ft_split(split, ' ');
	fill_in(temp);
	while (pipe_split[i] != NULL)
	{
		if (pipe_split[i][0] == 39)
			i = list_single_quote(&temp, pipe_split, i);
		else if (pipe_split[i][0] == 34)
			i = list_double_quote(&temp, pipe_split, i, env);
		else if (pipe_split[i][0] == '<' && pipe_split[i][1] == '<')
			i = list_heredoc(&temp, pipe_split, i, env);
		else if (pipe_split[i][0] == '<' && pipe_split[i][1] == '\0')
			i = list_infile(&temp, pipe_split, i);
		else if (pipe_split[i][0] == '>' && pipe_split[i][1] == '\0')
			i = list_outfile(&temp, pipe_split, i);
		else
			list_word(&temp, pipe_split[i]);
		i++;
	}
	return (0);
}

void	exec_init(t_node *command_table)
{
	command_table->command = ft_split(command_table->words, ' ');
	while (command_table->next != NULL)
	{
		command_table = command_table->next;
		command_table->command = ft_split(command_table->words, ' ');
	}
}

void	command_table(char **split, char **envp, t_envp *env)
{
	t_node			*node;
	t_node			*temp;
	char			**command_split;
	int				i;

	node = create_head(split[0]);
	i = 1;
	while (split[i] != '\0')
	{
		lstadd_back(&node, split[i]);
		i++;
	}
	i = 0;
	temp = node;
	while (temp != NULL)
	{
		split_pipe(split[i], temp, env);
		temp = temp->next;
		i++;
	}
	exec_init(node);
	if ((commands_built(node, env, envp) == 0))
		q_pipex_start(node, envp);
	// q_pipex_start(node, envp);
	// list_print_command(node);
}
