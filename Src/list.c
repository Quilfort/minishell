/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 12:11:17 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/06/20 11:13:45 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*lstlast(t_node *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

static t_node	*lstnew(char *split)
{
	t_node	*newcontent;

	newcontent = (t_node *)malloc(sizeof(t_node));
	if (!newcontent)
		return (NULL);
	newcontent->content = split;
	newcontent->next = NULL;
	return (newcontent);
}

void	lstadd_back(t_node **lst, char *split)
{
	t_node	*temp;
	t_node	*new;

	new = lstnew(split);
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	else
	{
		temp = lstlast(*lst);
		temp->next = new;
	}
}

static t_node	*create_head(char *first)
{
	t_node	*head;

	head = (t_node *)malloc(sizeof(t_node));
	if (head == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	head->content = first;
	head->next = NULL;
	return (head);
}

t_node	*create_list(char *head)
{
	t_node	*list;
	int		argv_index;
	list = create_head(head);
	return (list);
}