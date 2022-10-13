/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_command_table.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 15:13:19 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/13 16:12:26 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_init(t_node *command_table)
{
	if (command_table->heredoc != NULL)
	{
		// printf("1\n\n");
		command_table->words = ft_strjoin(command_table->words, " ");
		command_table->words = ft_strjoin(command_table->words, "tmpfile");
		// printf("2\n\n");
	}
	// printf("3\n\n");
	command_table->command = ft_split(command_table->words, ' ');
	// printf("4\n\n");
	while (command_table->next != NULL)
	{
		// printf("5\n\n");
		command_table = command_table->next;
		// printf("6\n\n");
		if (command_table->heredoc != NULL)
		{
			// printf("7\n\n");
			command_table->words = ft_strjoin(command_table->words, " ");
			command_table->words = ft_strjoin(command_table->words, "tmpfile");
			// printf("8\n\n");
		}
		// printf("9\n\n");
		
		command_table->command = ft_split(command_table->words, ' ');
		// printf("10\n\n");
	}
// 	printf("11\n\n");
}

int	make_pipes(char *split, int i)
{
	while (split[i] != '|' && split[i] != '\0')
	{
		if (split[i] == 34)
		{
			i++;
			while (split[i] != '\0' && split[i] != 34)
				i++;
		}
		else if (split[i] == 39)
		{
			i++;
			while (split[i] != '\0' && split[i] != 39)
				i++;
		}
		i++;
	}
	return (i);
}

int	add_to_list(t_node *node, int i, char *split)
{
	char	*content;
	int		start;

	start = i;
	i = make_pipes(split, i);
	content = ft_substr(split, start, (i - start));
	lstadd_back(&node, content);
	// free(content);
	i++;
	return (i);
}

t_node	*create_command_table_list(char *split, t_envp *env, t_vars *vars)
{
	t_node			*node;
	t_node			*temp;
	char			*string;
	int				i;

	i = 0;
	i = make_pipes(split, i);
	string = ft_substr(split, 0, i);
	node = create_head(string);
	i++;
	while (split[i] != '\0')
	{
		i = add_to_list(node, i, split);
	}
	temp = node;
	while (temp != NULL)
	{
		split_pipe(temp->content, temp, env, vars);
		temp = temp->next;
	}
	// free(string);
	return (node);
}

void	command_table(char *split, t_envp *env, t_vars *vars)
{
	t_node			*node;

	node = create_command_table_list(split, env, vars);
	exec_init(node);
	if (node->command[0] == NULL)
	{
		wait(NULL);
		free(node);
	}
	else
	{
		if ((ft_strncmp("exit", node->command[0], 4) == 0) \
			&& (node->command[1] == NULL) \
			&& ft_strlen("exit") == ft_strlen(node->command[0]))
		{
			ft_putendl_fd("exit", 1);
			exit(0);
		}
		if (builtin(node, env, vars) == 0)
			q_pipex_start(node, vars);
		unlink("tmpfile");
		// list_print_command(node);
		// free_command(node);

	}
}

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