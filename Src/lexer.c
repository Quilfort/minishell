/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 15:13:19 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/08/15 14:27:19 by qfrederi      ########   odam.nl         */
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
		// printf("\ntoken %d:  ", i);
		// printf("%d\n", list->token);
		printf("\nwords %d:  ", i);
		printf("%s\n", list->words);
		printf("\ninfile %d:  ", i);
		printf("%s\n", list->infile);
		printf("\noutfile %d:  ", i);
		printf("%s\n", list->outfile);


		list = list->next;
		i++;
	}
}

static void fill_in(t_node *temp)
{
	temp->words = ft_strdup("");
	temp->infile = ft_strdup("");
	temp->outfile = ft_strdup("");
}


static char split_pipe(char *split, t_node *temp)
{
	char	**pipe_split;
	int i;

	i = 0;
	pipe_split = ft_split(split, ' ');
	fill_in(temp);
	while (pipe_split[i] != NULL)
	{

		if (pipe_split[i][0] == '<' && pipe_split[i][1] == '\0')
			i = list_infile(&temp, pipe_split, i);
		else if (pipe_split[i][0] == '>' && pipe_split[i][1] == '\0')
			i = list_outfile(&temp, pipe_split, i);
		else
			list_word(&temp, pipe_split[i]);	
		i++;
	}
	return (0);	
}

void	command_table(char **split, char **envp)
{
	t_node			*node;
	t_node			*temp;
	char			**command_split;
	int				i;

	node = create_list(split[0]);
	i = 1;
	while (split[i] != '\0')
	{
		lstadd_back(&node,split[i], 0);
		i++;
	}
	i = 0;
	temp = node;
	while (temp != NULL)
	{
		split_pipe(split[i], temp);
		temp = temp->next;
		i++;
	}
	list_print_command(node);
}
