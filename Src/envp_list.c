/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 15:35:29 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/12 15:59:22 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envp	*lstlast_envp(t_envp *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

static t_envp	*lstnew_envp(char *split, int token)
{
	t_envp	*newcontent;

	newcontent = (t_envp *)malloc(sizeof(t_envp));
	if (!newcontent)
		return (NULL);
	newcontent->content = split;
	newcontent->next = NULL;
	return (newcontent);
}


void	lstadd_back_envp(t_envp **lst, char *split, int token)
{
	t_envp	*temp;
	t_envp	*new;

	new = lstnew_envp(split, token);
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	else
	{
		temp = lstlast_envp(*lst);
		temp->next = new;
	}
}

t_envp	*create_head_envp(char *first)
{
	t_envp	*head;

	head = (t_envp *)malloc(sizeof(t_envp));
	if (head == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	head->content = first;
	head->next = NULL;
	return (head);
}

t_envp	*create_list_envp(char *head)
{
	t_envp	*list;
	
	list = create_head_envp(head);
	return (list);
}