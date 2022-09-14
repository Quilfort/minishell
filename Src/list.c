/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 12:11:17 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/14 15:07:57 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lstsize(t_node *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

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

t_node	*create_head(char *first)
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
