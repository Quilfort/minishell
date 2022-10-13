/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_command_table.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 15:13:19 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/13 19:35:19 by rharing       ########   odam.nl         */
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
			command_table->words = ft_strjoin_free(command_table->words, "tmpfile");
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
		// printf("\nheredoc %d:  ", i);
		// printf("%s\n", list->heredoc);
		printf("\ncommand[0] %d:  ", i);
		printf("%s\n", list->command[0]);
		printf("end of node!!\n");
		list = list->next;
		i++;
	}
}

t_node	*create_command_table_list(char *split, t_envp *env, t_vars *vars)
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
		split_pipe(temp->content, temp, env, vars);
		temp = temp->next;
	}
	return (node);
}

void	free_command(t_node *list)
{
	t_node	*temp;
	size_t	i;

	while (list != NULL)
	{
		i = 0;
		temp = list;
		free(temp->words);
		free(temp->content);
		free(temp->heredoc);
		free(temp->infile);
		free(temp->outfile);
		while (temp->command[i] != NULL)
		{
			free(temp->command[i]);
			i++;
		}
		free(temp->command);
		free(temp);
		list = list->next;
	}
}

void	freesplit1(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	command_table(char *split, t_envp *env, t_vars *vars)
{
	t_node			*node;

	node = create_command_table_list(split, env, vars);
	exec_init(node);
	// list_print_command(node);
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
		free_command(node);
		freesplit1(vars->path);
		// free(vars->path);
	}
}
