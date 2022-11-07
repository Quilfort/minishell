/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_command_table.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 15:13:19 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/04 14:02:51 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_init(t_node *command_table)
{
	if (command_table->heredoc != NULL)
	{
		command_table->words = ft_strjoin_free(command_table->words, " ");
		command_table->words = ft_strjoin_free(command_table->words, "tmpfile");
	}
	command_table->command = ft_split(command_table->words, ' ');
	while (command_table->next != NULL)
	{
		command_table = command_table->next;
		if (command_table->heredoc != NULL)
		{
			command_table->words = ft_strjoin_free(command_table->words, " ");
			command_table->words = ft_strjoin_free(command_table->words, \
			"tmpfile");
		}
		command_table->command = ft_split(command_table->words, ' ');
	}
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
	int		start;

	start = i;
	i = make_pipes(split, i);
	lstadd_back(&node, ft_substr(split, start, (i - start)));
	i++;
	return (i);
}

t_node	*create_command_table_list(char *split, t_envp *env)
{
	t_node			*node;
	t_node			*temp;
	int				i;

	i = 0;
	i = make_pipes(split, i);
	node = create_head(ft_substr(split, 0, i));
	i++;
	while (split[i] != '\0')
	{
		i = add_to_list(node, i, split);
	}
	temp = node;
	while (temp != NULL)
	{
		split_pipe(temp->content, temp, env);
		temp = temp->next;
	}
	return (node);
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

void	command_table(char *split, t_envp *env, t_vars *vars)
{
	t_node			*node;

	node = create_command_table_list(split, env);
	exec_init(node);
	if (node->next == NULL)
		openfiles(node, vars);
	// list_print_command(node);
	if (node->command[0] == NULL && node->next == NULL)
		close_files(vars, node);
	else
	{
		exit_now_questionmark(node);
		if (node->next == NULL)
		{
			if (builtin(node, env, vars) == 0)
				q_pipex_start(node, vars, env);
		}
		else
		{	
			q_pipex_start(node, vars, env);
			freesplit(vars->path);
		}
		unlink("tmpfile");
	}
	free_command(node);
}
